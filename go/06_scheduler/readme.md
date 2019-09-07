# Simple Scheduler

**Motivation**: 
I was really curious about how programs perform scheduled tasks/cronjobs. So I wanted to create a dumb task scheduler that perform tasks according to a specified scheduled. 

**Task**:
Create a scheduler that performs tasks according to a specified scheduled. 
Think about the abstraction of tasks/jobs, the data structure(s) needed, and the main driver/loop to perform those scheduled tasks/jobs. 

**My dumb solution** 
I started by imagining that programs that perform jobs are essentially just an infinite loop that checks every s amount of time for jobs to perform. The loop isn't concerned with what the job is, all it does is perform the job. Therefore, I need to abstract tasks/jobs into a simple interface that simply implements two methods, `getTime() time.Time` and `doTask()`. Thus, the main loop of the scheduler will retrieve all tasks of time t and call `doTask()` to perform those tasks without any concerns regarding what the hell `doTask()` actually does. `getTime()` on the other hand will be used as a key for task ts to be stored in map[time.Time][]task. 

And I know, my code is super horrible for this one. I had less than 30 minutes to write it before starting work at 9. 
