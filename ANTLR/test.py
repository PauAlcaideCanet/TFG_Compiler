from antlr4 import *
from testLexer import testLexer
from testParser import testParser

input_stream = InputStream(input('? '))
lexer = testLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = testParser(token_stream)
tree = parser.root()
print(tree.toStringTree(recog=parser))