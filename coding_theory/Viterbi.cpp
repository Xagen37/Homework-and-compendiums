#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Predeclarations of data structures used further
vector<vector<int>> g; // Generator matrix of the given code
vector<int> info;      // Input for Encode
vector<int> encoded;   // Encoding result: a codeword of the given code
vector<double> word;   // Input for Decode: a noisy vector
vector<int> decoded;   // Output of Decode: probably-fixed codeword
mt19937 rgen(37);

// Add values from the second vector to the first.
// As we work in binary arithmetics, addition is xor.
void inc_vec(vector<int>& res, const vector<int>& rhs)
{
    for (int i = 0; i < res.size(); i++)
    {
        res[i] ^= rhs[i];
    }
}

// Performs forward traverse of adaptation of the Gauss algorithm.
// It makes all the row beginnings in the matrix unique.
// With the reverse_Gauss converts the matrix to MSF.
void straight_Gauss(vector<vector<int>>& matrix)
{
    const int row = matrix.size(), col = matrix[0].size();
    int curr_row = 0, curr_col = 0;
    for (; curr_row < row && curr_col < col;)
    {
        if (matrix[curr_row][curr_col])
        {
            for (int j = curr_row + 1; j < row; j++)
            {
                if (matrix[j][curr_col])
                {
                    inc_vec(matrix[j], matrix[curr_row]);
                }
            }
            curr_row++;
            curr_col++;
        }
        else
        {
            bool found_one = false;
            for (int j = curr_row + 1; j < row; j++)
            {
                if (matrix[j][curr_col])
                {
                    inc_vec(matrix[curr_row], matrix[j]);
                    found_one = true;
                    break;
                }
            }
            if (found_one)
            {
                // repeat again with the same row and col
            }
            else
            {
                curr_col++;
            }
        }
    }
}

// Performs backward traverse of adaptation of the Gauss algorithm.
// It makes all the row endings in the matrix unique.
// With the straight_Gauss converts the matrix to MSF.
void reverse_Gauss(vector<vector<int>>& matrix)
{
    // Maintain list of rows with not unique endings.
    vector<int> not_spanned(matrix.size());
    iota(not_spanned.begin(), not_spanned.end(), 0);
    for (int col = matrix[0].size() - 1; col >= 0 && not_spanned.size(); col--)
    {
        int fix_row = -1;
        // Start traversing from the last rows, because adding them to other rows
        // won't break invariant of unique beginnings.
        for (int row = matrix.size() - 1; row >= 0; row--)
        {
            // We don't care about rows, that already have unique endings
            if (matrix[row][col] && count(not_spanned.begin(), not_spanned.end(), row))
            {
                if (fix_row == -1)
                {
                    // If it's the first `1` in the column, fix the row.
                    fix_row = row;
                }
                else
                {
                    // If it's not the first `1`, remove it by adding fixed row.
                    inc_vec(matrix[row], matrix[fix_row]);
                }
            }
        }
        // If we fixed any new row, remove it from `not-unique-list`
        if (fix_row != -1)
        {
            not_spanned.erase(
                remove(
                    not_spanned.begin(), not_spanned.end(), fix_row
                ), 
                not_spanned.end()
            );
        }
    }
}

// Multiplicates vector by matrix. Used for encoding.
void mul_vec_mat(const vector<int>& lhs, const vector<vector<int>>& rhs, vector<int>& res)
{
    const int cols = rhs[0].size();
    res.resize(cols);
    for (int i = 0; i < cols; i++)
    {
        int sum = false;
        for (int row = 0; row < rhs.size(); row++)
        {
            sum ^= (lhs[row] & rhs[row][i]);
        }
        res[i] = sum;
    }
}

// Struct for aggregating inner trellis of decoder.
struct Trellis
{
    // We will view node's id as a bitmask, equal to linear combination of active rows.
    using id_t = uint32_t;
    // One layer of the trellis, corresponds to one column of generating matrix.
    struct Layer
    {
        // Set of active rows of the generating matrix for current layer.
        // Row is active, if the corresponding column is in the row's span.
        // Sorted set is used to maintain stable order, because we heavily use bitmasks.
        set<int> active_rows;

        // Vector of the layer's nodes.
        // Each node is implicitly characterized by its index in the vector, i.e. id.
        // Each node has vector of outcoming edges. If building the trellis
        // from matrix in MSF, the vector's maximum size is 2.
        // An edge is pair of node id, where the edge is directed, and a weight,
        // that is symbol (0 or 1) for the edge
        vector<vector<pair<id_t, bool>>> transitions;
    };

    vector<Layer> layers;

    Trellis() = default;

    // Take generator matrix in Minimal Span Form as input and build trellis out of it.
    Trellis(const vector<vector<int>>& matrix)
    {
        const int row_n = matrix.size(), col_n = matrix[0].size();
        // Count span intervals for matrix's rows
        vector<pair<int, int>> spans(row_n);
        for (int i = 0; i < row_n; i++)
        {
            int start = -1, finish = -1;
            for (int j = 0; j < col_n; j++)
            {
                if (matrix[i][j])
                {
                    start = j;
                    break;
                }
            }
            for (int j = col_n - 1; j >= 0; j--)
            {
                if (matrix[i][j])
                {
                    finish = j;
                    break;
                }
            }
            spans[i] = { start + 1, finish + 1 };
        }

        layers.resize(col_n + 1);
        // The first and the last layers have only one vertex: start and finish.
        layers.front().transitions.resize(1);
        layers.back().transitions.resize(1);

        // Build the trellis using backward dynamic programming
        for (int col = 1; col <= col_n; col++)
        {
            set<int>& prev_active = layers[col - 1].active_rows;
            set<int>& active = layers[col].active_rows;
            // Collect all the rows, that are active for the layer.
            // Row is active, if the corresponding to that layer column lies in the row's span.
            for (int i = 0; i < spans.size(); i++)
            {
                if (spans[i].first <= col && col < spans[i].second)
                {
                    active.insert(i);
                }
            }

            // Each layer has 2^(number of active rows) vertexes,
            // corresponding to all possible linear combinations of active rows.
            layers[col].transitions.resize(1 << active.size());

            // Copy current column's values from the matrix for simplicity and speeding up.
            vector<int> matrix_col(matrix.size());
            for (int i = 0; i < matrix_col.size(); i++)
            {
                matrix_col[i] = matrix[i][col - 1];
            }

            const int prev_size = layers[col - 1].transitions.size();
            const int curr_size = layers[col].transitions.size();
            for (int prev_it = 0; prev_it < prev_size; prev_it++)
            {
                for (int curr_it = 0; curr_it < curr_size; curr_it++)
                {
                    // Firstly, we have to check, if there any edges
                    // from previous node to the current one.
                    // There is an edge, if for both linear combinations
                    // equal active rows have the same coefficients, i.e. they both are 1 or 0
                    bool has_path = true;
                    int prev_active_cnt = 0;
                    for (int prev_row : prev_active)
                    {
                        int active_cnt = 0;
                        for (int curr_row : active)
                        {
                            if (prev_row == curr_row)
                            {
                                bool is_prev_flipped = (prev_it & (1 << prev_active_cnt));
                                bool is_curr_flipped = (curr_it & (1 << active_cnt));
                                if (is_prev_flipped != is_curr_flipped)
                                {
                                    has_path = false;
                                }
                            }
                            active_cnt++;
                        }
                        prev_active_cnt++;
                    }
                    if (!has_path)
                    { continue; }

                    // We take union here, because if a new active row appeared
                    // in the current layer, we have to take it in account.
                    set<int> active_rows;
                    set_union(prev_active.begin(), prev_active.end(),
                              active.begin(), active.end(),
                              inserter(active_rows, active_rows.end()));

                    // Copy out numbers of active rows, because it's
                    // easier to perform operations with vectors.
                    vector<bool> active_row_elements;
                    active_row_elements.reserve(active_rows.size());
                    vector<bool> active_matrix_elements;
                    active_matrix_elements.reserve(active_rows.size());
                    int cnt = 0;
                    for (int row : active_rows)
                    {
                        if (prev_active.count(row))
                        {
                            // Current active row was active in the previous layer.
                            // Proceed with the old mask.
                            active_row_elements.push_back(prev_it & (1 << cnt));
                            cnt++;
                        }
                        else
                        {
                            // Current active row appeared first time in the current layer.
                            // Take the last (i.e. highest) bit of the new mask for it.
                            // There may be only one such row, because MSF doesn't allow
                            // several rows to start or end simultaneously.
                            active_row_elements.push_back(curr_it & (1 << (active.size() - 1)));
                        }

                        active_matrix_elements.push_back(matrix_col[row]);
                    }

                    // The weight of the vector is dot product of active rows in the
                    // current combination and the corresponding values from the generating matrix.
                    bool weight = 0;
                    for (int i = 0; i < active_matrix_elements.size(); i++)
                    {
                        weight = weight ^ (active_row_elements[i] & active_matrix_elements[i]);
                    }

                    // Add the new edge to our structure.
                    layers[col - 1].transitions[prev_it].push_back({ curr_it, weight });
                }
            }
        }

    }
};

// Declaration for easy use further.
Trellis trellis;

// Vectors used in decoding.
// Vector of distances for dynamic programming.
vector<vector<double>> dists;
// Vector for saving and restoring the best path.
// path[i][j] holds the id of the previous node in the best path
// and value of the edge used in the path.
vector<vector<pair<Trellis::id_t, int>>> path;

// Decode given noisy vector and store in into decoded.
void decode(const vector<double>& word, const Trellis& trellis, vector<int>& decoded)
{
    // Flush vectors' states to initial one
    for (int i = 0; i < dists.size(); i++)
    {
        dists[i].assign(trellis.layers[i].transitions.size(), DBL_MAX);
    }

    for (int i = 0; i < path.size(); i++)
    {
        path[i].assign(dists[i].size(), { -1, -1 });
    }

    dists[0][0] = 0;
    path[0][0] = { 0, -1 };
    // We use forward dynamic programming here, so the trellis is
    // traversed layer to layer, node to node.
    for (int layer = 0; layer < dists.size() - 1; layer++)
    {
        for (Trellis::id_t node = 0; node < dists[layer].size(); node++)
        {
            const vector<pair<Trellis::id_t, bool>>& edges = trellis.layers[layer].transitions[node];
            double& curr_dist = dists[layer][node];
            // Look through all the outcoming edges
            for (const auto& edge : edges)
            {
                // Count possible new distanse
                double next_dist = curr_dist + word[layer] * (edge.second ? 1 : 0);
                double& old_next_dist = dists[layer + 1][edge.first];
                if (next_dist < old_next_dist)
                {
                    // If the current path is better, relax the distance
                    // and store info about the previous node.
                    old_next_dist = next_dist;
                    path[layer + 1][edge.first] = { node, edge.second ? 1 : 0 };
                }
            }
        }
    }

    // Restore the path by going from the end up to the beginning.
    Trellis::id_t curr_node = 0;
    vector<int> steps; steps.reserve(decoded.size());
    for (int i = dists.size() - 1; i > 0; i--)
    {
        steps.push_back(path[i][curr_node].second);
        curr_node = path[i][curr_node].first;
    }

    reverse(steps.begin(), steps.end());

    decoded = move(steps);
}

double simulate(double noise, int max_iter, int max_err)
{
    const double n = g[0].size();
    const double k = g.size();
    // This distribution generates numbers according to the Gaussian distribution.
    normal_distribution<> dis(0, sqrt(0.5 * pow(10, -noise / 10) * (n / k)));
    int it_cnt = 1, err_cnt = 0;

    for (; it_cnt <= max_iter && err_cnt < max_err; it_cnt++)
    {
        // Generate an info vector
        for (int i = 0; i < info.size(); i++)
        {
            info[i] = rgen() % 2;
        }

        // Encode the info vector
        mul_vec_mat(info, g, encoded);

        // Add random gaussian noise to the encoded vector
        for (int i = 0; i < word.size(); i++)
        {
            word[i] = (encoded[i] ? -1.0 : 1.0) + dis(rgen);
        }

        // Try to restore the initial encoded codeword out of the noisy vector.
        decode(word, trellis, decoded);

        for (int i = 0; i < decoded.size(); i++)
        {
            if (decoded[i] != encoded[i])
            {
                err_cnt++;
                break;
            }
        }
    }
    return static_cast<double>(err_cnt) / it_cnt;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    g.resize(k, vector<int>(n));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
        }
    }

    // Make copy of the generating matrix to be able to perform all the operations in-place.
    vector<vector<int>> msf_g = g;
    // Performing forward and reverse traversals, we convert the matrix to Minimal Spanning Form.
    straight_Gauss(msf_g);
    reverse_Gauss(msf_g);
    // After converting the matrix to MSF, it is possible to
    // build trellis for Viterbi decoding algorithm.
    trellis = Trellis(msf_g);
    for (const auto& layer : trellis.layers)
    {
        cout << layer.transitions.size() << ' ';
    }
    cout << '\n';

    string command;
    info.resize(k);
    encoded.resize(n);
    word.resize(n);
    decoded.resize(n);
    dists.resize(trellis.layers.size());
    for (int i = 0; i < dists.size(); i++)
    {
        dists[i].resize(trellis.layers[i].transitions.size(), DBL_MAX);
    }
    path.resize(dists.size());
    for (int i = 0; i < path.size(); i++)
    {
        path[i].resize(dists[i].size());
    }

    while (cin >> command)
    {
        if (command == "Encode")
        {
            for (int i = 0; i < k; i++)
            {
                cin >> info[i];
            }

            // Encoding is simply multiplying info vector by generating matrix.
            mul_vec_mat(info, g, encoded);

            for (int val : encoded)
            {
                cout << val << ' ';
            }
            cout << '\n';

            continue;
        }
        if (command == "Decode")
        {
            for (int i = 0; i < n; i++)
            {
                cin >> word[i];
            }

            decode(word, trellis, decoded);

            for (int val : decoded)
            {
                cout << val << ' ';
            }
            cout << '\n';
            continue;
        }
        if (command == "Simulate")
        {
            double noise;
            int max_iter, max_err;
            cin >> noise >> max_iter >> max_err;
            cout << simulate(noise, max_iter, max_err) << '\n';
            continue;
        }
        cout << "FAILURE\n";
    }
    return 0;
}