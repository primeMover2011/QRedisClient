# QRedisClient

A cross platform driver for Redis written entirely in Qt/C++ with no funky dependancies.

# Goals

- Windows support (really, really, really!)
- Simple straightforward usage and integration into existing code
- Native of API look and feel.
- Minimize the use of free-form strings.

# Features

- Probably at least a few
- that are likely to change
- as this is still in early
- development. Some of them
- could be good though. :)

# // TODO :)
- Multi connection broker.
- Threading

# FAQ

**Q: Doesn't this already exist?**

**A:** Not that I've found / been able to compile. Many C/C++ drivers depend on [hiredis](https://github.com/redis/hiredis) which I was not able to compile on Windows, even the standalone parser bits.

**Q: Isn't there already a QRedisClient library?**

**A:** Yes, and it's brilliant! [qredisclient](https://github.com/uglide/qredisclient) Again though, it did not compile on Windows and relied on hiredis.

**Q: Y U GOTTA BE STEALING NAMES ALL TIME ALL TIME?**

**A:** It was not intentional but also not easily or satisfactorily OCD avoidable. This is a module for Qt, it is a Redis client, and UpperCamelCase looks better.

!BOOOOOOOM!, QRedisClient. :trollface:

# Changelog
--
**v_1.0.0, August 26th 2016**
    
    Fixes:
        - Many
        
    Improvements:
        - Various bits and bobs.
 
    API Changes:
        - Hope you like red exclamation points!
