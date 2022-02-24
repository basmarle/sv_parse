#from graphviz import Digraph
# gra = Digraph()
# gra.node("a", "Machine Learning Errors")
# gra.node("b", "RMSE")
# gra.node("c", "MAE")
# gra.edges(["ab", "ac"])
#
# print(gra.source)
#
# gra.render('Machine.gv', view=True)

import graphviz


p = graphviz.Graph(name='parent')
p.node("bas")
c = graphviz.Graph(name='cluster_child')
d = graphviz.Graph(name='cluster_child')

c.node("b")
d.node("c")

p.subgraph(c)
p.subgraph(d)
print(p.source)
p.render('Machine.gv', view=True)
