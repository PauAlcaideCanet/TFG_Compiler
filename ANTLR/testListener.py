# Generated from test.g4 by ANTLR 4.13.2
from antlr4 import *
if "." in __name__:
    from .testParser import testParser
else:
    from testParser import testParser

# This class defines a complete listener for a parse tree produced by testParser.
class testListener(ParseTreeListener):

    # Enter a parse tree produced by testParser#root.
    def enterRoot(self, ctx:testParser.RootContext):
        pass

    # Exit a parse tree produced by testParser#root.
    def exitRoot(self, ctx:testParser.RootContext):
        pass


    # Enter a parse tree produced by testParser#expr.
    def enterExpr(self, ctx:testParser.ExprContext):
        pass

    # Exit a parse tree produced by testParser#expr.
    def exitExpr(self, ctx:testParser.ExprContext):
        pass



del testParser