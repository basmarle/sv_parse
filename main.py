import os
import sys

from hdlConvertorAst.language import Language
from hdlConvertor import HdlConvertor
from hdlConvertorAst.to.json import ToJson
from hdlConvertorAst.hdlAst import HdlModuleDef
from hdlConvertorAst.hdlAst import HdlCompInst
from HdlModel import Module

from graphviz import Digraph

def get_module_def(root_node, name):
    for node in root_node.objs:
        if isinstance(node, HdlModuleDef) and node.module_name.val == name:
            return node

def print_all_sub(root, graph):
    for node in root.objs:
        if not isinstance(node, HdlCompInst):
            continue

        #gra.node(node.module_name.val, node.module_name.val)

        new_graph = Digraph(name=f'cluster_{node.module_name.val}')
        new_graph.node(f"bas{node.module_name.val}")
        print(node.module_name.val)
        if(len(node.objs) > 0):
            print_all_sub(node, new_graph)

        graph.subgraph(new_graph)

def get_root_node():
    filenames = ["dff_async_reset.v"]
    include_dirs = []
    c = HdlConvertor()
    return c.parse(filenames, Language.SYSTEM_VERILOG, include_dirs, hierarchyOnly=False, debug=True)


def parse_all_modules(root, modules):
    for node in root.objs:
        if not isinstance(node, HdlModuleDef):
            continue

        new_mod = Module()
        new_mod.name = node.module_name.val

        for obj in node.objs:
            if isinstance(obj, HdlCompInst):
                new_mod.instances[obj.name.val] = obj.module_name.val

        modules.append(new_mod)


def main():
    modules = []
    gra = Digraph(name='main', comment='main')

    root_node = get_root_node()
    parse_all_modules(root_node, modules)
    print(modules)

    main_node = get_module_def(root_node, "main")
    print_all_sub(main_node, gra)
    gra.render('Machine.gv', view=True)
    print(gra.source)
    return

    for o in d.objs:
        print(type(o.dec))
        if isinstance(o, HdlModuleDef):
            print(o.module_name)
            for x in o.dec.ports:
                print(x.name)

if __name__ == "__main__":
    main()