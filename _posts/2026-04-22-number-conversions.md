---
title: "Conversion Questions and Answers"
description: "This is a question and answer section, involving the conversion between decimal, binary and hexadecimal number systems, for a purpose of practice and understanding."
type: doubt
tags: [number-systems]
---

I had a doubt - should I memorize the hex values for everything? Nope. Not necessary. All I need to remember is only 0 to 9 and A to F : their binary stuffs. 

# Number Systems 

A single byte consists of 8 bits. In **binary notation**, it's value is from 00000000 base 2 to 11111111 base 2. When we are viewing the same as a decimal number, then it's value ranges from 0 to 255. But we cannot be writing long 0s and 1s or just a decimal notation to accurately describe how the computer models it. Instead, we write the bit patterns as base 16. 

> A byte is 8 bits. And each byte can be represented as a 16 character hex value. But this is architecture dependent and is always not fixed. We will come to that later. 

```
In the hexadecimal system, we have : 
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F 
where it corresponds to 
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
in the decimal number system. 
The binary equivalent of them is :
0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111

```

## Hex to Bin

Suppose you are given a number `0x173A4C` : obvious conditions- 

- When something starts with `0x` having similar pattern, it is exactly a hexadecimal notation. 
- It would contain only 0 to 9 and A to F. 
- It can be expressed as both uppercase and lowercase or even mixed case. 

How am I supposed to convert this into a binary number?

- Eject the 0x, take the leftover part. 
- In our case it is : `173A4C`
- Map them correspondingly : 

1 -> 0001 
7 -> 0111 
3 -> 0011 
A -> 1010 
4 -> 0100 
C -> 1100 

This gives us the binary repr : `000101110011101001001100`


## Bin to Hex

Now, suppose we are going to do a reverse operation -> convert the binary back to hexadecimal, we follow these steps. 

- Group them as 4 from right to left. 
- If there were any bits in the left that are dangling, ie not grouped into 4, pad it with 0s in the front of it. 
- Evaluate the hex value from group of 4 bin values. 

For example, say, you are given this number : `1111001010110110110011`
Find the hex value, then : 

- group: 1100 1101 1011 0101 0011 11 (from right end)
- reverse: 11 1100 1010 1101 1011 0011 
- pad: 0011 1100 1010 1101 1011 0011 
- convert: 3 C A D B 3 
- represent in hex notation: `0x3CADB3`

Done, this is how we convert stuffs.

## Representing Powers of 2 

In the C programming, most of the buffers are in the form of powers of 2, ie, have value like 1024, 2048, 4096, etc. These can be compactly notated as powers of 2. 

> Note that the binary notation of 2 is 0010. The truth about this is : 2<sup>1</sup> = 1 followed by 1 zero and left padded = 0010.

Similarly, we can express any power of two as the following : 

- 2<sup>n</sup> = 1 followed by n zeros. 
- In hexadecimal, one hex 0 is equivalent to 4 binary zeros, ie 0 base 16 = 0000 base 2.
- Hence, n = i + 4j, where we can write 2<sup>n</sup> as 2<sup>i + 4j</sup>.
- If i is 0, 1, 2, 3 : we have the leading digit in the hex as 1, 2, 4, 8. When it goes to i = 4, it becomes exactly represented as hex base 16.
- Note that we are reverse engineering why exactly n = i + 4j and not 2i + 2j or something like that. Because, hex has base 16, which equals 2<sup>4</sup> and a hex can represent exactly 4 binary digits.
- Therefore, 2<sup>n</sup> can be represented in hex as 2<sup>i</sup> followed by j hex zeros. 

Congrats!. Successfull reverse engineering. 

=> 2<sup>11</sup> = 2<sup>3 + 2.4</sup> = in hex : 0x2<sup>i</sup>0000... j times.
=> which is i = 3, j = 2, hence 2<sup>11</sup> = 0x800 

> Finally, accomplished the doubt session, ie, a question session.

