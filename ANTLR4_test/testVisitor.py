# Generated from test.g4 by ANTLR 4.13.2
from antlr4 import *
if "." in __name__:
    from .testParser import testParser
else:
    from testParser import testParser

# This class defines a complete generic visitor for a parse tree produced by testParser.

class testVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by testParser#root.
    def visitRoot(self, ctx:testParser.RootContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by testParser#expr.
    def visitExpr(self, ctx:testParser.ExprContext):
        return self.visitChildren(ctx)



del testParser