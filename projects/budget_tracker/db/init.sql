CREATE TABLE IF NOT EXISTS transactions (
  id SERIAL PRIMARY KEY,
  description VARCHAR(255),
  amount DECIMAL(10, 2),
  date DATE
);
