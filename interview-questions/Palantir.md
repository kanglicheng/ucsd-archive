𝗣𝗮𝗹𝗮𝗻𝘁𝗶𝗿
Was really weird. Personally, I had one of the best phone screens of my life with them; objectively thought I destroyed the question, as I got the answer the interviewer was looking for really fast, was talking all the time, and coded it up pretty quickly. Was left with ~15-20 minutes remaining. Didn’t get past the phone screen.
1. Implement a minimal sentence search engine that supports two functions: void put(String sentence, int id), and List<int> query(String word). query takes in a single word. We are willing to trade inefficiencies in put() if it means gaining optimizations in query().
eg) put(“I hate interview prepping with a passion”, 1)
put(“I’m a dirty weeb and I love anime with a passion”, 2) 
query(“passion”) returns <1, 2>
query(“Hatoko-chan”) returns <>
𝘍𝘰𝘭𝘭𝘰𝘸-𝘶𝘱: support exact phrases in your search engine.
eg) put(“If you badmouth my waifu, I swear I’ll stab you to death with a spoon”, 1)
put(“I swear that death by spoon is a long and painful process”, 2) 
query(“death spoon”) returns <> because even though both sentences #1 and #2 contain “death” and “spoon”, neither has the exact phrase “death spoon”. 
query(“I swear”) returns <1, 2>