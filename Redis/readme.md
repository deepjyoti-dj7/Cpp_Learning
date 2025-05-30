# 🚀 Redis + Node.js – Complete Guide

This guide explains how to set up and use Redis with Node.js, covering essential Redis concepts with practical code examples.

---

## 📚 Table of Contents

1. [What is Redis?](#what-is-redis)
2. [Installing Redis on Windows](#installing-redis-on-windows)
3. [Installing Node.js & Redis Client](#installing-nodejs--redis-client)
4. [Connecting Node.js to Redis](#connecting-nodejs-to-redis)
5. [Core Redis Concepts in Node.js](#core-redis-concepts-in-nodejs)
   - Strings
   - Hashes
   - Lists
   - Sets
   - Sorted Sets
6. [Expiration (TTL)](#expiration-ttl)
7. [Pub/Sub](#pubsub)
8. [Caching Example](#caching-example)
9. [Basic Queue Example](#basic-queue-example)
10. [Rate Limiting Example](#rate-limiting-example)
11. [Best Practices](#best-practices)
12. [Resources](#resources)

---

## 🧠 What is Redis?

**Redis** (Remote Dictionary Server) is an open-source, in-memory data structure store, used as a database, cache, and message broker.

---

## 🪟 Installing Redis on Windows

1. **Download Redis Windows build**:
   - Redis is not natively supported on Windows but you can use **Memurai** (Redis-compatible) or **WSL (Windows Subsystem for Linux)**.

### Option 1: Use Memurai (Best for Production)

- Download: https://www.memurai.com/
- Install and run Memurai as a Windows service.

### Option 2: Use Redis via WSL

```bash
# In PowerShell
wsl --install

# Inside WSL terminal
sudo apt update
sudo apt install redis-server
redis-server
```

````

---

## 🧰 Installing Node.js & Redis Client

### Install Node.js:

- Download from: [https://nodejs.org/](https://nodejs.org/)
- Confirm installation:

```bash
node -v
npm -v
```

### Install Redis Client Library:

```bash
npm install redis
```

---

## 🔌 Connecting Node.js to Redis

```js
const redis = require("redis");

const client = redis.createClient({
  url: "redis://localhost:6379",
});

client.on("error", (err) => console.error("Redis Client Error", err));

(async () => {
  await client.connect();
  console.log("Connected to Redis");
})();
```

---

## 🧱 Core Redis Concepts in Node.js

### 📦 Strings

```js
await client.set("greeting", "Hello, Redis!");
const value = await client.get("greeting");
console.log(value); // Hello, Redis!
```

### 🗃️ Hashes

```js
await client.hSet("user:1", { name: "Alice", age: "30" });
const user = await client.hGetAll("user:1");
console.log(user); // { name: 'Alice', age: '30' }
```

### 📋 Lists

```js
await client.rPush("tasks", "task1", "task2");
const task = await client.lPop("tasks");
console.log(task); // task1
```

### 📚 Sets

```js
await client.sAdd("tags", "nodejs", "redis", "backend");
const tags = await client.sMembers("tags");
console.log(tags); // ['nodejs', 'redis', 'backend']
```

### 🏅 Sorted Sets

```js
await client.zAdd("scores", [
  { score: 100, value: "Alice" },
  { score: 200, value: "Bob" },
]);
const top = await client.zRange("scores", 0, -1, { WITHSCORES: true });
console.log(top); // ['Alice', '100', 'Bob', '200']
```

---

## ⏳ Expiration (TTL)

```js
await client.set("session", "abc123", { EX: 10 }); // Expires in 10 seconds
const ttl = await client.ttl("session");
console.log(`Expires in ${ttl} seconds`);
```

---

## 📣 Pub/Sub

### Publisher

```js
await client.publish("channel", "Hello from publisher!");
```

### Subscriber

```js
const subscriber = client.duplicate();
await subscriber.connect();

await subscriber.subscribe("channel", (message) => {
  console.log(`Received: ${message}`);
});
```

---

## 🚀 Caching Example

```js
async function getUser(id) {
  const cacheKey = `user:${id}`;
  const cached = await client.get(cacheKey);

  if (cached) return JSON.parse(cached);

  const user = { id, name: "John Doe" }; // Simulated DB call
  await client.set(cacheKey, JSON.stringify(user), { EX: 60 });
  return user;
}
```

---

## 📨 Basic Queue Example

### Producer

```js
await client.rPush("emailQueue", JSON.stringify({ to: "user@example.com" }));
```

### Consumer

```js
setInterval(async () => {
  const job = await client.lPop("emailQueue");
  if (job) {
    const email = JSON.parse(job);
    console.log(`Sending email to ${email.to}`);
  }
}, 1000);
```

---

## ⚖️ Rate Limiting Example

```js
async function isRateLimited(ip) {
  const key = `rate:${ip}`;
  const count = await client.incr(key);

  if (count === 1) {
    await client.expire(key, 60); // 60-second window
  }

  return count > 10;
}
```

---

## ✅ Best Practices

- Use `EX` or `TTL` to avoid stale data.
- Avoid blocking commands like `KEYS *` in production.
- Use `client.duplicate()` for Pub/Sub or parallel streams.
- Secure Redis (even locally) with authentication when needed.

---

## 🔗 Resources

- [Redis Documentation](https://redis.io/docs/)
- [Node Redis Client](https://github.com/redis/node-redis)
- [Memurai for Windows](https://www.memurai.com/)
- [BullMQ (Redis Job Queue)](https://docs.bullmq.io/)
- [RedisInsight GUI](https://redis.com/redis-enterprise/redis-insight/)

---
````
