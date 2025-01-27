#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"
#include "timer.h"

Timer* CreateTimer(){
    Timer *timer = (Timer *)malloc(sizeof(Timer));
    if(timer==NULL){
        printf("Memory allocation failed for timer\n");
        exit(1);
    }
    timer->Duration=0.0f;
    printf("timer created\n");
    return timer;
}
void StartTimer(Timer *timer,float duration){
    if(duration<=0) return;
    if (timer==NULL){
        printf("timer is null\n");
        return;
    };
    timer->Duration=duration;
    printf("Timer Started\n");
}

void UpdateTimer(Timer *t){
    if(t!=NULL && t->Duration>0) t->Duration-=GetFrameTime();
}

bool TimerHasFinished(Timer *t){
    if(t!=NULL) return t->Duration<=0;
    return false;
}


