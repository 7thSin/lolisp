namespace signals {
    static map<int, obj*> sigcalls;
    void exec(int s) {
        auto sigcall = sigcalls.find(s);
        if (sigcall != sigcalls.end())
            eval(sigcall->second); // execute lambda
        else if (interactive) {
            if (::debugger(DBG_TERM, "\nSignal received.")->car.value)  // enter debugger session
                exit(0);
        }
        else {
            signal(s, SIG_DFL); // reset the signal handler
            raise(s);           // reraise signal 
        }
    }
    void init() {
        signal(SIGTERM, exec);
        signal(SIGINT, exec);
        signal(SIGUSR1, exec);
        signal(SIGUSR2, exec);
    }
    void set(int sig, obj* lambda) {
        sigcalls.insert({ sig, lambda });
    }
}
