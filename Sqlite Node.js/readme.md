````markdown
insert user
curl -X POST http://localhost:3000/users -H "Content-Type: application/json" -d '{"name":"Alice", "email":"alice@example.com"}'

fetch all users
curl http://localhost:3000/users

Here's a detailed `README.md` file covering all important **SQLite concepts with Node.js** on **Windows**, including installation, usage, and code examples:

---

# 🗃️ SQLite + Node.js on Windows – Complete Guide

This guide explains how to set up and use SQLite with Node.js on **Windows**, including key SQLite concepts and examples using the `sqlite3` and `better-sqlite3` packages.

---

## 📚 Table of Contents

1. [What is SQLite?](#what-is-sqlite)
2. [Installing SQLite on Windows](#installing-sqlite-on-windows)
3. [Using SQLite in Node.js](#using-sqlite-in-nodejs)
4. [Setting Up a Database](#setting-up-a-database)
5. [Core SQLite Operations](#core-sqlite-operations)
   - Create Table
   - Insert Data
   - Query Data
   - Update Data
   - Delete Data
6. [Using better-sqlite3 (Alternative)](#using-better-sqlite3-alternative)
7. [Best Practices](#best-practices)
8. [Resources](#resources)

---

## 🧠 What is SQLite?

**SQLite** is a lightweight, serverless, self-contained SQL database engine. It stores all data in a single `.sqlite` or `.db` file and is widely used in embedded systems and small apps.

---

## 🪟 Installing SQLite on Windows

1. Download precompiled binaries:
   - https://www.sqlite.org/download.html
2. Extract and place `sqlite3.exe` in a folder (e.g., `C:\sqlite`)
3. Add folder to system `PATH`:
   - Open System Properties → Environment Variables → Add `C:\sqlite` to `Path`

### Test in CMD:

```bash
sqlite3
```
````

---

## 📦 Using SQLite in Node.js

### 1. Initialize Project

```bash
mkdir sqlite-node-app && cd sqlite-node-app
npm init -y
npm install sqlite3
```

---

## ⚙️ Setting Up a Database

```js
const sqlite3 = require("sqlite3").verbose();

// Connect to or create database file
const db = new sqlite3.Database("./mydb.sqlite", (err) => {
  if (err) console.error(err.message);
  else console.log("Connected to SQLite database.");
});
```

---

## 🔨 Core SQLite Operations

### 🏗️ Create Table

```js
db.run(`
  CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    email TEXT UNIQUE
  )
`);
```

### ➕ Insert Data

```js
const stmt = db.prepare("INSERT INTO users (name, email) VALUES (?, ?)");
stmt.run("Alice", "alice@example.com");
stmt.finalize();
```

### 🔍 Query Data

```js
db.all("SELECT * FROM users", [], (err, rows) => {
  if (err) throw err;
  rows.forEach((row) => console.log(row));
});
```

### ✏️ Update Data

```js
db.run("UPDATE users SET name = ? WHERE id = ?", ["Alicia", 1]);
```

### ❌ Delete Data

```js
db.run("DELETE FROM users WHERE id = ?", [1]);
```

---

## 🚀 Using `better-sqlite3` (Alternative)

For sync and faster performance, use:

```bash
npm install better-sqlite3
```

### Example:

```js
const Database = require("better-sqlite3");
const db = new Database("mydb.sqlite");

// Create table
db.prepare(
  `CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)`
).run();

// Insert
db.prepare("INSERT INTO users (name) VALUES (?)").run("Bob");

// Query
const users = db.prepare("SELECT * FROM users").all();
console.log(users);
```

---

## 🧠 Best Practices

- Use `try-catch` or error-first callbacks.
- Avoid string interpolation in SQL – use placeholders (`?`) to prevent SQL injection.
- Use `better-sqlite3` for performance-sensitive or synchronous workflows.
- Keep database files out of public folders.
- Back up `.sqlite` files regularly in production.

---

## 🔗 Resources

- [SQLite Official Docs](https://sqlite.org/docs.html)
- [sqlite3 npm](https://www.npmjs.com/package/sqlite3)
- [better-sqlite3](https://github.com/WiseLibs/better-sqlite3)
- [SQLite GUI Tool: DB Browser](https://sqlitebrowser.org/)
- [W3Schools SQLite Tutorial](https://www.w3schools.com/sql/sql_intro.asp)

```

```
