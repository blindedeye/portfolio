document.getElementById('transaction-form').addEventListener('submit', async (e) => {
    e.preventDefault();
    const description = document.getElementById('description').value;
    const amount = document.getElementById('amount').value;
    const date = document.getElementById('date').value;
  
    const response = await fetch('/api/transactions', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ description, amount, date }),
    });
  
    const transaction = await response.json();
    addTransactionToDOM(transaction);
  });
  
  async function loadTransactions() {
    const response = await fetch('/api/transactions');
    const transactions = await response.json();
    transactions.forEach(addTransactionToDOM);
  }
  
  function addTransactionToDOM(transaction) {
    const transactionsDiv = document.getElementById('transactions');
    
    // Create transaction div
    const div = document.createElement('div');
    div.textContent = `${transaction.description} - $${transaction.amount} on ${transaction.date}`;
    
    // Create delete button
    const deleteButton = document.createElement('button');
    deleteButton.textContent = 'Delete';
    deleteButton.style.marginLeft = '10px';
    
    // Add click event to delete the transaction
    deleteButton.addEventListener('click', async () => {
      const response = await fetch(`/api/transactions/${transaction.id}`, {
        method: 'DELETE',
      });
      
      if (response.ok) {
        transactionsDiv.removeChild(div); // Remove the transaction from the DOM
      }
    });
    
    // Append delete button to transaction div
    div.appendChild(deleteButton);
    
    // Append transaction div to transactions list
    transactionsDiv.appendChild(div);
  }
  
  
  loadTransactions();
  