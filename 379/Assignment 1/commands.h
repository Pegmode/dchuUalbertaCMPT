pid_t spawnChildProcess(struct CommandContainer,bool);
bool checkForArg(char*, char **,int);
void execProcess(struct CommandContainer);
bool removeFromPTable(pid_t);
bool killProcess(pid_t);
void displayResourcesUsed();
int searchForPIDPos(pid_t);
void killAllBackgroundProcesses();
int getProcessCPUTime(pid_t);
void stdoutToFile(struct CommandContainer , char*);// >
void fileToStdin(struct CommandContainer , char*);// <
