//run this command: sudo apt-get install libbluetooth-dev
//compile gcc -o rfcomm-server rfcomm-server.c -lbluetooth

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bluetooth.h"
#include "rfcomm.h"
#include "servo.h"
#include <string>

using namespace std;

void move_up(servo &s){
    float d = s.getDegree();
    //printf("the degree is : %f\n",d);
    if(d < 0) d = 90;
    s.setDegree(d-5);
}

void move_down(servo &s){
    float d = s.getDegree();
    //printf("the degree is : %f\n",d);
    if(d > 180) d = 90;
    s.setDegree(d+5);
}

string convert(int size, char* buf){
    string temp = "";
    for(int i = 0; i< size; i++){
        temp += buf[i];
    }
    return temp;
}

int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    //loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    servo s1(0,90);
    servo s2(1,90);
    while(1){
            bytes_read = read(client, buf, sizeof(buf));
            if( bytes_read > 0 ) {
                    //printf("received [%s]\n", buf);
                string temp = convert(bytes_read,buf);
                cout << temp << endl;
                if(temp == "up"){
                    printf("up\n");
                    move_up(s1);
                }else{
                    printf("Down\n");
                    move_down(s1);
                }
            }
    }
  

    // close connection
    close(client);
    close(s);
    return 0;
}
