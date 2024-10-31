const express = require('express');
const { Pool } = require('pg');
const path = require('path');
require('dotenv').config();

const app = express();
const port = process.env.PORT || 3000;

// PostgreSQL connection pool
const pool = new Pool({
  user: process.env.DB_USER,
  host: process.env.DB_HOST,
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: process.env.DB_PORT,
});

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// Routes
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.get('/api/transactions', async (req, res) => {
  try {
    const result = await pool.query('SELECT * FROM transactions');
    res.json(result.rows);
  } catch (error) {
    res.status(500).send(error.message);
  }
});

app.post('/api/transactions', async (req, res) => {
  const { description, amount, date } = req.body;
  try {
    const result = await pool.query(
      'INSERT INTO transactions (description, amount, date) VALUES ($1, $2, $3) RETURNING *',
      [description, amount, date]
    );
    res.json(result.rows[0]);
  } catch (error) {
    res.status(500).send(error.message);
  }
});

app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});

// Delete a transaction by id
app.delete('/api/transactions/:id', async (req, res) => {
    const { id } = req.params;
    try {
      const result = await pool.query('DELETE FROM transactions WHERE id = $1 RETURNING *', [id]);
      if (result.rowCount === 0) {
        return res.status(404).send('Transaction not found');
      }
      res.status(200).json({ message: 'Transaction deleted', transaction: result.rows[0] });
    } catch (error) {
      res.status(500).send(error.message);
    }
  });
  