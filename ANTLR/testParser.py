# Generated from test.g4 by ANTLR 4.13.2
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,6,40,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,1,0,1,1,1,1,1,1,1,1,
        1,1,1,1,5,1,17,8,1,10,1,12,1,20,9,1,1,2,1,2,1,2,1,2,1,2,1,2,5,2,
        28,8,2,10,2,12,2,31,9,2,1,3,1,3,1,3,1,3,1,3,3,3,38,8,3,1,3,0,2,2,
        4,4,0,2,4,6,0,0,38,0,8,1,0,0,0,2,10,1,0,0,0,4,21,1,0,0,0,6,37,1,
        0,0,0,8,9,3,2,1,0,9,1,1,0,0,0,10,11,6,1,-1,0,11,12,3,4,2,0,12,18,
        1,0,0,0,13,14,10,2,0,0,14,15,5,2,0,0,15,17,3,4,2,0,16,13,1,0,0,0,
        17,20,1,0,0,0,18,16,1,0,0,0,18,19,1,0,0,0,19,3,1,0,0,0,20,18,1,0,
        0,0,21,22,6,2,-1,0,22,23,3,6,3,0,23,29,1,0,0,0,24,25,10,2,0,0,25,
        26,5,3,0,0,26,28,3,6,3,0,27,24,1,0,0,0,28,31,1,0,0,0,29,27,1,0,0,
        0,29,30,1,0,0,0,30,5,1,0,0,0,31,29,1,0,0,0,32,33,5,4,0,0,33,34,3,
        2,1,0,34,35,5,5,0,0,35,38,1,0,0,0,36,38,5,6,0,0,37,32,1,0,0,0,37,
        36,1,0,0,0,38,7,1,0,0,0,3,18,29,37
    ]

class testParser ( Parser ):

    grammarFileName = "test.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "<INVALID>", "'+'", "'*'", "'('", "')'" ]

    symbolicNames = [ "<INVALID>", "NEWLINE", "PLUS", "MULT", "OPEN_PAR", 
                      "CLOSE_PAR", "INT" ]

    RULE_root = 0
    RULE_e = 1
    RULE_t = 2
    RULE_f = 3

    ruleNames =  [ "root", "e", "t", "f" ]

    EOF = Token.EOF
    NEWLINE=1
    PLUS=2
    MULT=3
    OPEN_PAR=4
    CLOSE_PAR=5
    INT=6

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.2")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class RootContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def e(self):
            return self.getTypedRuleContext(testParser.EContext,0)


        def getRuleIndex(self):
            return testParser.RULE_root




    def root(self):

        localctx = testParser.RootContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_root)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 8
            self.e(0)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class EContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def t(self):
            return self.getTypedRuleContext(testParser.TContext,0)


        def e(self):
            return self.getTypedRuleContext(testParser.EContext,0)


        def PLUS(self):
            return self.getToken(testParser.PLUS, 0)

        def getRuleIndex(self):
            return testParser.RULE_e



    def e(self, _p:int=0):
        _parentctx = self._ctx
        _parentState = self.state
        localctx = testParser.EContext(self, self._ctx, _parentState)
        _prevctx = localctx
        _startState = 2
        self.enterRecursionRule(localctx, 2, self.RULE_e, _p)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 11
            self.t(0)
            self._ctx.stop = self._input.LT(-1)
            self.state = 18
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,0,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    localctx = testParser.EContext(self, _parentctx, _parentState)
                    self.pushNewRecursionContext(localctx, _startState, self.RULE_e)
                    self.state = 13
                    if not self.precpred(self._ctx, 2):
                        from antlr4.error.Errors import FailedPredicateException
                        raise FailedPredicateException(self, "self.precpred(self._ctx, 2)")
                    self.state = 14
                    self.match(testParser.PLUS)
                    self.state = 15
                    self.t(0) 
                self.state = 20
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,0,self._ctx)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.unrollRecursionContexts(_parentctx)
        return localctx


    class TContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def f(self):
            return self.getTypedRuleContext(testParser.FContext,0)


        def t(self):
            return self.getTypedRuleContext(testParser.TContext,0)


        def MULT(self):
            return self.getToken(testParser.MULT, 0)

        def getRuleIndex(self):
            return testParser.RULE_t



    def t(self, _p:int=0):
        _parentctx = self._ctx
        _parentState = self.state
        localctx = testParser.TContext(self, self._ctx, _parentState)
        _prevctx = localctx
        _startState = 4
        self.enterRecursionRule(localctx, 4, self.RULE_t, _p)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 22
            self.f()
            self._ctx.stop = self._input.LT(-1)
            self.state = 29
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,1,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    localctx = testParser.TContext(self, _parentctx, _parentState)
                    self.pushNewRecursionContext(localctx, _startState, self.RULE_t)
                    self.state = 24
                    if not self.precpred(self._ctx, 2):
                        from antlr4.error.Errors import FailedPredicateException
                        raise FailedPredicateException(self, "self.precpred(self._ctx, 2)")
                    self.state = 25
                    self.match(testParser.MULT)
                    self.state = 26
                    self.f() 
                self.state = 31
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,1,self._ctx)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.unrollRecursionContexts(_parentctx)
        return localctx


    class FContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def OPEN_PAR(self):
            return self.getToken(testParser.OPEN_PAR, 0)

        def e(self):
            return self.getTypedRuleContext(testParser.EContext,0)


        def CLOSE_PAR(self):
            return self.getToken(testParser.CLOSE_PAR, 0)

        def INT(self):
            return self.getToken(testParser.INT, 0)

        def getRuleIndex(self):
            return testParser.RULE_f




    def f(self):

        localctx = testParser.FContext(self, self._ctx, self.state)
        self.enterRule(localctx, 6, self.RULE_f)
        try:
            self.state = 37
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [4]:
                self.enterOuterAlt(localctx, 1)
                self.state = 32
                self.match(testParser.OPEN_PAR)
                self.state = 33
                self.e(0)
                self.state = 34
                self.match(testParser.CLOSE_PAR)
                pass
            elif token in [6]:
                self.enterOuterAlt(localctx, 2)
                self.state = 36
                self.match(testParser.INT)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx



    def sempred(self, localctx:RuleContext, ruleIndex:int, predIndex:int):
        if self._predicates == None:
            self._predicates = dict()
        self._predicates[1] = self.e_sempred
        self._predicates[2] = self.t_sempred
        pred = self._predicates.get(ruleIndex, None)
        if pred is None:
            raise Exception("No predicate with index:" + str(ruleIndex))
        else:
            return pred(localctx, predIndex)

    def e_sempred(self, localctx:EContext, predIndex:int):
            if predIndex == 0:
                return self.precpred(self._ctx, 2)
         

    def t_sempred(self, localctx:TContext, predIndex:int):
            if predIndex == 1:
                return self.precpred(self._ctx, 2)
         




