#include <iostream>
#include <slang/compilation/Compilation.h>
#include <slang/syntax/SyntaxTree.h>
#include <slang/syntax/SyntaxVisitor.h>
#include <slang/compilation/SemanticModel.h>
#include "Module.h"

using namespace slang;

class TestVisitor : public SyntaxVisitor<TestVisitor> {
public:
    Compilation compilation;
    SemanticModel model;
    std::vector<Module> modules;
    Module *currentModule;

    TestVisitor(const std::shared_ptr<SyntaxTree> &tree) :
            model(compilation) {
        compilation.addSyntaxTree(tree);
    }

    // TODO FUNCTIONS
    void handle(const FunctionDeclarationSyntax &decl) {
//        std::cout << "BEGIN FunctionDeclarationSyntax" << std::endl;
//        auto portList = decl.prototype->portList;
//        if (!portList)
//            return;
//        std::cout << decl.prototype->name->toString() << std::endl;
//        std::cout << portList->ports.size() << std::endl;
//        for (auto port : portList->ports) {
//            std::cout << port->toString() << std::endl;
//        }
//        std::cout << "END FunctionDeclarationSyntax" << std::endl;
    }

    // TODO MODULE
    void handle(const ModuleHeaderSyntax &decl) {
        currentModule = new Module(decl.name.toString());
        visitDefault(decl);
        modules.push_back(*currentModule);
        delete currentModule;
        currentModule = 0;
//        std::cout << "BEGIN ModuleHeaderSyntax" << std::endl;
//        std::cout << decl.name.toString() << std::endl;
//        if (decl.ports->isKind(SyntaxKind::AnsiPortList)) {
//            std::cout << ((AnsiPortListSyntax*)decl.ports)->ports.size() << std::endl;
//        }
//        std::cout << "END ModuleHeaderSyntax" << std::endl;
    }

    void handle(const HierarchyInstantiationSyntax &decl) {
        std::cout << decl.toString() << std::endl;
    }

    // TODO MODULEPORTS
    void handle(const AnsiPortListSyntax &decl) {
        if (!currentModule)
            return;

        for (auto port: decl.ports) {

            for (int i = 0; i < port->getChildCount(); i++) {
                auto child = port->childNode(i);
                if (child)
                    if(child->kind == SyntaxKind::Declarator)
                        currentModule->ports.push_back(child->toString());
                else {
                    auto token = port->childToken(i);
                    if (token)
                        std::cout << "ERROR WE HAVE A TOKEN WHICH WE DO NOT EXPECT WHAAAAAAAAAAAA" << std::endl;
                }
            }
        }
//        std::cout << "BEGIN AnsiPortListSyntax" << std::endl;
//        for(auto port : decl.ports) {
//            std::cout << port->toString() << std::endl;
//        }
//
//        std::cout << "END AnsiPortListSyntax" << std::endl;
    }

    // TODO MODULE INSTANTIATION
};


// TODO Lets try to draw all the modules
void draw() {

}

int main() {
    auto tree_text2 = SyntaxTree::fromText(R"(
    module M(input logic a, input logic bas);
         typedef enum int { FOO = 1, BAR = 2, BAZ = 3 } test_t;

         function void foo(int i, output r);
         endfunction

         function void bar(int bas, output bas2);
         endfunction
    endmodule
)");
    auto tree_text = SyntaxTree::fromText(R"(
    module aap(input logic a, input logic bas);
    endmodule
    module M(input logic a, input logic bas);
    aap bas_instance(1'b1, 1'b1);
    endmodule
)");

    auto treeVisitor = TestVisitor(tree_text);
    tree_text->root().visit(treeVisitor);

    for (auto module : treeVisitor.modules) {
        std::cout << module.name << std::endl;

        for(auto port : module.ports) {
            std::cout << port << std::endl;
        }
    }
    //SyntaxTree::fromFile("/home/encya/dev/TrivialMIPS/src/ThinPad.sv");

    return 0;
}


//#include <iostream>
//#include "slang/syntax/SyntaxTree.h"
//
//using namespace slang;
//int main() {
//
//    //auto tree_text = SyntaxTree::fromFile("/home/labuser/dev/my-systemverilog-examples/systems/microprocessors/programable-8-bit-microprocessor/programable-8-bit-microprocessor.v");
//    auto tree_text = SyntaxTree::fromText("module m; endmodule");
//    auto root = tree_text->root();
//
//    std::cout << root.getChildCount() << std::endl;
//    for (int i = 0; i < root.getChildCount(); ++i) {
//        auto child_token = root.childToken(i);
//        auto child_node = root.childNode(i);
//        auto token = root.getFirstToken();
//        std::cout << child_token.toString() << std::endl;
//        std::cout << child_node->toString() << std::endl;
//    }
//
//    return 0;
//}