````markdown
# 📘 MongoDB Full Reference Guide

This document provides a comprehensive overview of **MongoDB**, a popular NoSQL database designed for high performance, high availability, and easy scalability. It includes core concepts, examples, and advanced usage.

---

## 📌 Table of Contents

1. [Introduction](#introduction)
2. [MongoDB vs SQL](#mongodb-vs-sql)
3. [Data Modeling](#data-modeling)
4. [CRUD Operations](#crud-operations)
5. [Query Operators](#query-operators)
6. [Indexes](#indexes)
7. [Aggregation Framework](#aggregation-framework)
8. [Schema Design Best Practices](#schema-design-best-practices)
9. [Transactions](#transactions)
10. [Replication & Sharding](#replication--sharding)
11. [Security](#security)
12. [Performance Tips](#performance-tips)
13. [Useful CLI & Shell Commands](#useful-cli--shell-commands)

---

## 🧠 Introduction

MongoDB is a **document-oriented NoSQL database** that stores data in flexible, JSON-like BSON documents. It's schema-less, making it ideal for applications with rapidly evolving data models.

---

## 🆚 MongoDB vs SQL

| Feature            | MongoDB               | SQL (e.g., MySQL/Postgres) |
| ------------------ | --------------------- | -------------------------- |
| Structure          | Document-based        | Table-based (Relational)   |
| Schema             | Dynamic               | Static                     |
| Joins              | Limited ($lookup)     | Native                     |
| Transactions       | Supported (since 4.0) | Native                     |
| Horizontal Scaling | Built-in (sharding)   | Complex                    |

---

## 🏗️ Data Modeling

MongoDB stores data as **documents** in collections.

```json
{
  "_id": ObjectId("..."),
  "name": "John Doe",
  "email": "john@example.com",
  "address": {
    "city": "Berlin",
    "zip": "10115"
  },
  "hobbies": ["reading", "cycling"]
}
```
````

> Collections ≈ Tables | Documents ≈ Rows | Fields ≈ Columns

---

## 🛠️ CRUD Operations

### Create

```js
db.users.insertOne({ name: "Alice", age: 28 });
db.users.insertMany([{ name: "Bob" }, { name: "Charlie" }]);
```

### Read

```js
db.users.find({ age: { $gt: 25 } });
db.users.findOne({ name: "Alice" });
```

### Update

```js
db.users.updateOne({ name: "Alice" }, { $set: { age: 29 } });
db.users.updateMany({}, { $inc: { age: 1 } });
```

### Delete

```js
db.users.deleteOne({ name: "Charlie" });
db.users.deleteMany({ age: { $lt: 18 } });
```

---

## 🔎 Query Operators

### Comparison

- `$eq`, `$ne`, `$gt`, `$gte`, `$lt`, `$lte`, `$in`, `$nin`

```js
db.products.find({ price: { $gte: 50, $lte: 100 } });
```

### Logical

- `$or`, `$and`, `$not`, `$nor`

```js
db.users.find({ $or: [{ age: { $lt: 20 } }, { age: { $gt: 60 } }] });
```

### Element

- `$exists`, `$type`

```js
db.users.find({ email: { $exists: true } });
```

---

## ⚡ Indexes

Indexes support fast query execution.

### Create Index

```js
db.users.createIndex({ name: 1 }); // Ascending
db.orders.createIndex({ orderDate: -1 }); // Descending
```

### Compound Index

```js
db.users.createIndex({ lastName: 1, firstName: 1 });
```

### Unique Index

```js
db.users.createIndex({ email: 1 }, { unique: true });
```

> Use `explain()` to understand index usage:

```js
db.users.find({ name: "John" }).explain("executionStats");
```

---

## 📊 Aggregation Framework

Used for complex data processing (filtering, grouping, transforming).

### Pipeline Stages

- `$match`, `$group`, `$project`, `$sort`, `$limit`, `$lookup`

### Example

```js
db.orders.aggregate([
  { $match: { status: "completed" } },
  { $group: { _id: "$customerId", total: { $sum: "$amount" } } },
  { $sort: { total: -1 } },
]);
```

### Join (via `$lookup`)

```js
db.orders.aggregate([
  {
    $lookup: {
      from: "users",
      localField: "userId",
      foreignField: "_id",
      as: "userInfo",
    },
  },
]);
```

---

## 🧬 Schema Design Best Practices

- Embed related data if 1:1 or 1\:few (denormalized).
- Use references (`ObjectId`) for many\:many relationships.
- Design based on **query patterns**, not strict normalization.
- Avoid deep nesting (performance, document size limit: 16MB).

---

## 🧾 Transactions

Supported for replica sets and sharded clusters (MongoDB 4.0+).

```js
const session = client.startSession();

session.withTransaction(() => {
  db1.users.insertOne({ name: "Alice" }, { session });
  db2.payments.insertOne({ user: "Alice", amount: 100 }, { session });
});
```

---

## 🌍 Replication & Sharding

### Replication

- Ensures **high availability**
- Replica Set = Primary + Secondary nodes

### Sharding

- Enables **horizontal scaling**
- Distributes data across multiple machines

---

## 🔐 Security

- Enable **authentication** and **authorization**
- Use **TLS/SSL** for secure communication
- Avoid exposing DB to public internet
- Configure **IP whitelisting**

```sh
# Create admin user
use admin
db.createUser({
  user: "admin",
  pwd: "password",
  roles: ["userAdminAnyDatabase", "readWriteAnyDatabase"]
});
```

---

## 🚀 Performance Tips

- Use **indexes** appropriately
- Avoid large `$in` queries
- Use **projection** to return only needed fields
- Monitor with `mongostat`, `mongotop`, and **MongoDB Atlas metrics**
- Use **schema validation** to catch incorrect data early

---

## 💻 Useful CLI & Shell Commands

```bash
# Connect to DB
mongo mongodb://localhost:27017/mydb

# List databases
show dbs

# List collections
use mydb
show collections

# Export data
mongoexport --db=mydb --collection=users --out=users.json

# Import data
mongoimport --db=mydb --collection=users --file=users.json
```
