#include "Parser.h"

// from graphviz
#include "cgraph.h"
#include "cdt.h"
#include "gvc.h"

int main()
{
    /*GVC_t* gvc = gvContext();
    Agraph_t* res_graph;
    char strings[][32] = {"val abacaba: Int = 0;",
                         "var C: String;",
                         "val value: Variable;",
                         " var bad_var : VeryBadVar = 13;"};
    std::string common = "example";
    for (int i = 0; i < 4; i++)
    {
        std::string filename = common + char(i + '0') + ".png";
        Parser p(strings[i]);
        res_graph = p.parse().as_cgraph();
        gvLayout(gvc, res_graph, "dot");
        gvRenderFilename(gvc, res_graph, "png", filename.c_str());
        gvFreeLayout(gvc, res_graph);
        agclose(res_graph);
    }

    gvFreeContext(gvc);*/
    std::string str = "var c: Int;";
    Parser p(str);
    p.parse();
    return 0;
}