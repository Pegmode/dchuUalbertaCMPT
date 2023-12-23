pid_t spawnChildProcess(struct CommandContainer,bool);
bool checkForArg(char*, char **,int);
void execProcess(struct CommandContainer);
void scanPTableForQuitters();