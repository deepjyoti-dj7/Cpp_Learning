insert user
curl -X POST http://localhost:3000/users -H "Content-Type: application/json" -d '{"name":"Alice", "email":"alice@example.com"}'

fetch all users
curl http://localhost:3000/users
