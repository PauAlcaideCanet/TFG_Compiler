# Generated from test.g4 by ANTLR 4.13.2
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
    from typing import TextIO
else:
    from typing.io import TextIO


def serializedATN():
    return [
        4,0,6,33,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,
        0,4,0,15,8,0,11,0,12,0,16,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,
        4,1,5,4,5,30,8,5,11,5,12,5,31,0,0,6,1,1,3,2,5,3,7,4,9,5,11,6,1,0,
        2,2,0,10,10,13,13,1,0,48,57,34,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,
        0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,1,14,1,0,0,0,3,20,1,0,0,0,
        5,22,1,0,0,0,7,24,1,0,0,0,9,26,1,0,0,0,11,29,1,0,0,0,13,15,7,0,0,
        0,14,13,1,0,0,0,15,16,1,0,0,0,16,14,1,0,0,0,16,17,1,0,0,0,17,18,
        1,0,0,0,18,19,6,0,0,0,19,2,1,0,0,0,20,21,5,43,0,0,21,4,1,0,0,0,22,
        23,5,42,0,0,23,6,1,0,0,0,24,25,5,40,0,0,25,8,1,0,0,0,26,27,5,41,
        0,0,27,10,1,0,0,0,28,30,7,1,0,0,29,28,1,0,0,0,30,31,1,0,0,0,31,29,
        1,0,0,0,31,32,1,0,0,0,32,12,1,0,0,0,3,0,16,31,1,6,0,0
    ]

class testLexer(Lexer):

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    NEWLINE = 1
    PLUS = 2
    MULT = 3
    OPEN_PAR = 4
    CLOSE_PAR = 5
    INT = 6

    channelNames = [ u"DEFAULT_TOKEN_CHANNEL", u"HIDDEN" ]

    modeNames = [ "DEFAULT_MODE" ]

    literalNames = [ "<INVALID>",
            "'+'", "'*'", "'('", "')'" ]

    symbolicNames = [ "<INVALID>",
            "NEWLINE", "PLUS", "MULT", "OPEN_PAR", "CLOSE_PAR", "INT" ]

    ruleNames = [ "NEWLINE", "PLUS", "MULT", "OPEN_PAR", "CLOSE_PAR", "INT" ]

    grammarFileName = "test.g4"

    def __init__(self, input=None, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.2")
        self._interp = LexerATNSimulator(self, self.atn, self.decisionsToDFA, PredictionContextCache())
        self._actions = None
        self._predicates = None


