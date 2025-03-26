/*

*/

#define NUM_GRAMMAR 1

#if (NUM_GRAMMAR == 1)
    //Define Automata 1
    #define NUM_TERMINALS 7
    #define TERMINALS {"T_INT","T_FLOAT","T_OPEN_PAR","T_CLOSE_PAR","T_SUM","T_MULT", "T_EOF"}
    #define NUM_NON_TERMINALS 4
    #define NON_TERMINALS {"S", "E", "T", "F"} 
    #define NUM_RULES 7
    #define PROD_RULES {    {{"T_NON_TERMINAL", "S"}, {{"T_NON_TERMINAL","E"}, {"T_EOF", ""}}, "2"}                             /*-Rule 0-*/, \
                            {{"T_NON_TERMINAL", "E"}, {{"T_NON_TERMINAL", "E"}, {"T_SUM", "+"}, {"T_NON_TERMINAL", "T"}}, "3"}    /*-Rule 1-*/, \
                            {{"T_NON_TERMINAL", "E"}, {{"T_NON_TERMINAL", "T"}}, "1"}                                         /*-Rule 2-*/, \
                            {{"T_NON_TERMINAL", "T"}, {{"T_NON_TERMINAL", "T"}, {"T_MULT", "*"}, {"T_NON_TERMINAL", "F"}}, "3"}   /*-Rule 3-*/, \
                            {{"T_NON_TERMINAL", "T"}, {{"T_NON_TERMINAL", "F"}}, "1"}                                         /*-Rule 4-*/, \
                            {{"T_NON_TERMINAL", "F"}, {{"T_OPEN_PAR", "("}, {"T_NON_TERMINAL", "E"}, {"T_CLOSE_PAR", ")"}}, "3"}  /*-Rule 5-*/, \
                            {{"T_NON_TERMINAL", "F"}, {{"T_INT", "NUM" }}, "1"}                                                   /*-Rule 6-*/, \
    }
    #define NUM_STATES 12
    #define ACCEPT_STATES {1}
    #define START_STATE 0

    //The columns are placed TERMINALS-NON_TERMINALS in the same order than above
    // La part del float no està implementat encara
    #define TRANSITIONS {   {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 1},{SHIFT, 2},{SHIFT, 3}},        /*-State 0-*/\
                            {{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 6},{ERROR, -1},{ACCEPT, 0},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1}},   /*-State 1-*/\
                            {{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{SHIFT, 7},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2}},   /*-State 2-*/\
                            {{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4},{REDUCE, 4}},  /*-State 3-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 8},{SHIFT, 2},{SHIFT, 3}},        /*-State 4-*/\
                            {{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6},{REDUCE, 6}},  /*-State 5-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 9},{SHIFT, 3}},       /*-State 6-*/\
                            {{SHIFT, 5},{SHIFT, 5},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 11},{ERROR, -1}},     /*-State 7-*/\
                            {{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 10},{SHIFT, 6},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1}},   /*-State 8-*/\
                            {{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{SHIFT, 7},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1}},   /*-State 9-*/\
                            {{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5},{REDUCE, 5}},  /*-State 10-*/\
                            {{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3},{REDUCE, 3}}   /*-State 11-*/\
}
    
#elif (NUM_GRAMMAR == 2)
    #define NUM_TERMINALS 5
    #define TERMINALS {"T_INT", "T_OPEN_PAR", "T_CLOSE_PAR", "T_SUM", "T_EOF"}
    #define NUM_NON_TERMINALS 2
    #define NON_TERMINALS {"S","E"} 
    #define NUM_RULES 3
    #define PROD_RULES {    { {"T_NON_TERMINAL", "S"}, { {"T_NON_TERMINAL", "E"} }, "1" },          /*-Rule 0-*/ \
                            { {"T_NON_TERMINAL", "E"}, { {"T_INT", "NUM"} }, "1" },                    /*-Rule 1-*/ \
                            { {"T_NON_TERMINAL", "E"}, { {"T_NON_TERMINAL", "E"}, {"T_SUM", "+"}, {"T_OPEN_PAR", "("}, {"T_NON_TERMINAL", "E"}, {"T_CLOSE_PAR", ")"} }, "5" } /*-Rule 2-*/ \
                        }
    #define NUM_STATES 7
    #define ACCEPT_STATES {2}
    #define START_STATE 0

    #define TRANSITIONS {   {{SHIFT, 1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 2}},            /*-State 0-*/\
                            {{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1},{REDUCE, 1}},          /*-State 1-*/\
                            {{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 3},{ACCEPT, 0},{ERROR, -1},{ERROR, -1}},           /*-State 2-*/\
                            {{ERROR, -1},{SHIFT, 4},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1}},           /*-State 3-*/\
                            {{SHIFT, 1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{ERROR, -1},{SHIFT, 5}},           /*-State 4-*/\
                            {{ERROR, -1},{ERROR, -1},{SHIFT, 6},{SHIFT, 3},{ERROR, -1},{ERROR, -1},{ERROR, -1}},           /*-State 5-*/\
                            {{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2},{REDUCE, 2}}           /*-State 6-*/\
                        }
    
#else
    #define NO_AUTOMATA_ERROR "NUM_GRAMMAR is not any automata option!"
#endif