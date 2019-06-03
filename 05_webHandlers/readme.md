# Calculator API 

*NOTE*: This is probably the stupidest exercise. But don't underestimate it, it'll help you learn the basics of routing in Go. I know, who the heck would need a calculator API? But hear me out, learning a language/tool is not necessarily done through building meaningful and useful stuff. But rather by building things that help us understand the fundamentals of the language. Then one day, my friend, when you're assigned a task to build an amazing tool that uses routing, you'll know how to do it :) I believe in you! 



**Task Description**: 

1. Build a `/calc` handler that takes three query parameters:
   1. `?op`, it specifies the operator. Support the following operators: `?op=add`, `?op=sub`, `?op=mult`, and `op=div`
   2. `?x`, it's the parameter for the first number. For example `x=15.1`
   3. `?y`, it's the parameter for the second number. For example, `y=14.023`
2. So, if someone wants to calculate  13.0 + 90, they'd make a request as follows `https://localhost:port/calc/?op=add&x=13.0&y=90` 
3. Make sure you implement the necessary validation. For example, `?op=rand&x=13.0&y=23` should return a message of invalid operator instead of crashing the session and throwing an error. 
4. Implement a root handler `/` that explains how to use the `/calc` API 



**Goals**:

1. Learn how to create a simple server in Go 
2. Learn how to implement routing in Go 
3. Learn how to read and process query parameters
4. Learn how to implement the necessary validation to avoid throwing errors. 