typedef struct {
    float Duration;
} Timer;
Timer* CreateTimer();
void StartTimer(Timer *timer,float duration);
void UpdateTimer(Timer *t);
bool TimerHasFinished(Timer *t);