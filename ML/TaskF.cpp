#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using obj_t = pair<vector<long long int>, long long int>;

struct Node
{
    int feat_id = -2;
    double border = -1;
    int left = -2;
    int right = -2;
    int clazz = -2;
    bool isLeaf = false;
};

vector<Node> tree;
int max_h, class_cnt;

int max_class(const vector<obj_t>& objects)
{
    vector<long long int> cnts(class_cnt);
    for (const obj_t& obj : objects)
    {
        cnts[obj.second - 1]++;
    }
    return max_element(cnts.begin(), cnts.end()) - cnts.begin() + 1;
}

void build_tree(int node_it, vector<obj_t>& objects, int h)
{
    Node& curr_node = tree[node_it];
    if (h == max_h)
    {
        curr_node.isLeaf = true;
        curr_node.clazz = max_class(objects);
        return;
    }

    auto mm = minmax_element(objects.begin(), objects.end(), [](const obj_t& lhs, const obj_t& rhs) { return lhs.second < rhs.second; });
    if (mm.first->second == mm.second->second)
    {
        curr_node.isLeaf = true;
        curr_node.clazz = mm.first->second;
        return;
    }

    vector<long long int> cnts_left(class_cnt), cnts_right(class_cnt);
    for (const obj_t& obj : objects)
    {
        cnts_right[obj.second - 1]++;
    }

    if (objects.size() > 50)
    {
        long long int csum_right = 0;
        for (size_t i = 0; i < cnts_right.size(); i++)
        {
            csum_right += cnts_right[i] * cnts_right[i];
        }

        const int m = objects[0].first.size();
        double best = DBL_MAX;
        int ideal_feat = -1;
        double ideal_border = -1;
        for (int i = 0; i < m; i++)
        {
            sort(objects.begin(), objects.end(), [i](const obj_t& lhs, const obj_t& rhs) { return lhs.first[i] < rhs.first[i]; });
            if (objects.front().first[i] == objects.back().first[i])
                continue;

            long long int sum_left = 0, sum_right = csum_right;
            long long int left_size = 0, right_size = objects.size();
            vector<long long int> to_left_cnt(cnts_left), to_right_cnt(cnts_right);
            size_t prev_it = 0;
            size_t it = 0;
            while (it < objects.size())
            {
                int count = 0;
                while (it < objects.size() && objects[prev_it].second == objects[it].second)
                {
                    it++;
                    count++;
                }
                if (it == objects.size())
                    break;

                int curr_cl = objects[prev_it].second - 1;
                long long int right_val = to_right_cnt[curr_cl];
                long long int left_val = to_left_cnt[curr_cl];

                sum_right -= right_val * right_val;
                sum_left -= left_val * left_val;

                to_right_cnt[curr_cl] -= count;
                to_left_cnt[curr_cl] += count;
                right_size -= count;
                left_size += count;


                right_val = to_right_cnt[curr_cl];
                left_val = to_left_cnt[curr_cl];

                sum_right += right_val * right_val;
                sum_left += left_val * left_val;

                double pleft = sum_left / static_cast<double>(left_size);
                double pright = sum_right / static_cast<double>(right_size);

                if (1.0 - pleft - pright < best)
                {
                    best = 1.0 - pleft - pright;
                    ideal_feat = i;
                    ideal_border = (objects[it - 1].first[i] + objects[it].first[i]) / 2.0;
                }

                prev_it = it;
            }
        }

        if (ideal_feat == -1)
        {
            curr_node.isLeaf = true;
            curr_node.clazz = max_class(objects);
            return;
        }

        curr_node.border = ideal_border;
        curr_node.feat_id = ideal_feat;

        vector<obj_t> to_left, to_right;
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (static_cast<double>(objects[i].first[ideal_feat]) < ideal_border)
            {
                to_left.push_back(objects[i]);
            }
            else
            {
                to_right.push_back(objects[i]);
            }
        }
        curr_node.left = tree.size();
        curr_node.right = tree.size() + 1;
        tree.emplace_back(Node());
        tree.emplace_back(Node());
        build_tree(tree[node_it].left, to_left, h + 1);
        build_tree(tree[node_it].right, to_right, h + 1);
    }
    else
    {
        const int m = objects[0].first.size();
        double best = DBL_MAX;
        int ideal_feat = -1;
        double ideal_border = -1;
        for (int i = 0; i < m; i++)
        {
            sort(objects.begin(), objects.end(), [i](const obj_t& lhs, const obj_t& rhs) { return lhs.first[i] < rhs.first[i]; });
            if (objects.front().first[i] == objects.back().first[i])
                continue;

            long long int left_size = 0, right_size = objects.size();
            vector<long long int> to_left_cnt(cnts_left), to_right_cnt(cnts_right);
            size_t prev_it = 0;
            size_t it = 0;
            while (it < objects.size())
            {
                int count = 0;
                while (it < objects.size() && objects[prev_it].second == objects[it].second)
                {
                    it++;
                    count++;
                }
                if (it == objects.size())
                    break;

                int curr_cl = objects[prev_it].second - 1;
                long long int right_val = to_right_cnt[curr_cl];
                long long int left_val = to_left_cnt[curr_cl];

                to_right_cnt[curr_cl] -= count;
                to_left_cnt[curr_cl] += count;
                right_size -= count;
                left_size += count;

                right_val = to_right_cnt[curr_cl];
                left_val = to_left_cnt[curr_cl];

                double pleft = 0.0, pright = 0.0;
                for (int biba = 0; biba < to_left_cnt.size(); biba++)
                {
                    if (!to_left_cnt[biba])
                        continue;

                    double p = to_left_cnt[biba] / static_cast<double>(left_size);
                    pleft -= p * log(p);
                }

                for (int boba = 0; boba < to_right_cnt.size(); boba++)
                {
                    if (!to_right_cnt[boba])
                        continue;

                    double p = to_right_cnt[boba] / static_cast<double>(right_size);
                    pright -= p * log(p);
                }

                if (pleft * left_size + pright * right_size < best)
                {
                    best = pleft * left_size + pright * right_size;
                    ideal_feat = i;
                    ideal_border = (objects[it - 1].first[i] + objects[it].first[i]) / 2.0;
                }

                prev_it = it;
            }
        }

        if (ideal_feat == -1)
        {
            curr_node.isLeaf = true;
            curr_node.clazz = max_class(objects);
            return;
        }

        curr_node.border = ideal_border;
        curr_node.feat_id = ideal_feat;

        vector<obj_t> to_left, to_right;
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (static_cast<double>(objects[i].first[ideal_feat]) < ideal_border)
            {
                to_left.push_back(objects[i]);
            }
            else
            {
                to_right.push_back(objects[i]);
            }
        }
        curr_node.left = tree.size();
        curr_node.right = tree.size() + 1;
        tree.emplace_back(Node());
        tree.emplace_back(Node());
        build_tree(tree[node_it].left, to_left, h + 1);
        build_tree(tree[node_it].right, to_right, h + 1);
    }
}

int main()
{
    int m; cin >> m >> class_cnt >> max_h;
    int n; cin >> n;

    vector<obj_t> objects(n);
    for (int i = 0; i < n; i++)
    {
        objects[i].first.resize(m);
        for (int j = 0; j < m; j++)
        {
            cin >> objects[i].first[j];
        }
        cin >> objects[i].second;
    }

    tree.emplace_back(Node());
    build_tree(0, objects, 0);

    cout << setprecision(20);
    cout << tree.size() << '\n';
    for (const Node& node : tree)
    {
        if (node.isLeaf)
        {
            cout << "C " << node.clazz << '\n';
        }
        else
        {
            cout << "Q " << node.feat_id + 1 << ' ' << node.border << ' ' << node.left + 1 << ' ' << node.right + 1 << '\n';
        }
    }

    return 0;
}