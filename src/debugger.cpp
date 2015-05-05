enum { 
    DBG_TERM = 0,
    DBG_REPLACE = 1,
};

obj* debugger(unsigned options = DBG_TERM, const char* message = NULL, obj* criminal = NULL) {
    const char* prompt = NULL;
    if (criminal)
        objdump(criminal);
    switch (options) {
        case DBG_TERM:
            prompt = "λ Quit? ";
            break;
        case DBG_REPLACE:
            prompt = "λ Enter a new value: ";
            break;
    }
    if (message)
        cout << message << endl;
    char* cmdline = readline(prompt);
    add_history(cmdline);
    size_t i = 0;
    string initialcmd = "(print " + string(cmdline) + ")";
    free(cmdline);
    obj* tree = lisp_tree(initialcmd, i);
    rl_on_new_line();
    return eval(tree);
}
