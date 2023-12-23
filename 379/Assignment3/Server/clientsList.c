//functions for interacting with ClientsList obj

void initClientsList(){//initialize Clients list
    g_clients_list.count = 0;
    g_clients_list.clients = (ClientTrack**) malloc(sizeof(ClientTrack) * MAX_CLIENTS);
}

bool addClient(char* name){//add a new client to clientlet (does not check for duplicate)
    if(g_clients_list.count >= MAX_CLIENTS){
        return false;
    }
    ClientTrack* client = (ClientTrack*) malloc(sizeof(ClientTrack));
    client->count = 0;
    strcpy(client->name, name);
    g_clients_list.clients[g_clients_list.count] = client;
    g_clients_list.count++;
    return true;
}

int searchForClient(char* name){//linear search for client by name, returns index of client or -1 if not found
    for(int i = 0; i < g_clients_list.count; i++){
        if(strcmp(name, g_clients_list.clients[i]->name) == 0){
            return i;
        }
    }
    return -1;
}

void incClientCount(char* name){//increment client transaction count with given name
    if(g_clients_list.count >= MAX_CLIENTS){
        printf("ERROR: TOO MANY CLIENTS, MAX %i\n", MAX_CLIENTS);
        return;
    }
    int clientIdx = searchForClient(name);
    if(clientIdx == -1){
        addClient(name);
        clientIdx = g_clients_list.count - 1;
    }
    g_clients_list.clients[clientIdx]->count++;
    return;
}

