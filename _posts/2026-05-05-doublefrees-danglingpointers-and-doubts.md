---
title: "Some Whys on the UB"
description: "This is about double frees, what happens when you access a freshly declared yet uninit value via a variable. Now that you free the memory, what happens when you access a freed memory? What about freeing two times? double frees. Note that we cannot predict that untill you compile - the compiler does not warn with normal flags, then you run it, boom, why did I encounter a SIGABRT due to a double free?"
type: doubt
tags: [undefined-behaviour, double-frees, dangling-pointers]
---




