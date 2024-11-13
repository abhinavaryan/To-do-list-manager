document.addEventListener('DOMContentLoaded', loadTasks);

document.getElementById('taskForm').addEventListener('submit', function(e) {
    e.preventDefault();
    const taskInput = document.getElementById('taskInput');
    const taskText = taskInput.value;

    fetch('/api/tasks', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ task: taskText })
    })
    .then(response => response.json())
    .then(data => {
        addTaskToList(data);
        taskInput.value = ''; // Clear input field
    });
});

function loadTasks() {
    fetch('/api/tasks')
        .then(response => response.json())
        .then(tasks => {
            tasks.forEach(task => addTaskToList(task));
        });
}

function addTaskToList(task) {
    const taskList = document.getElementById('taskList');
    const li = document.createElement('li');
    li.textContent = task.text;
    if (task.completed) {
        li.classList.add('completed');
    }

    // Mark task as completed
    li.addEventListener('click', function() {
        li.classList.toggle('completed');
        updateTaskCompletion(task.id, li.classList.contains('completed'));
    });

    // Edit button
    const editButton = document.createElement('button');
    editButton.textContent = 'Edit';
    editButton.className = 'edit';
    editButton.onclick = function(event) {
        event.stopPropagation(); // Prevent triggering the click event on the li
        const newTaskText = prompt("Edit your task:", task.text);
        if (newTaskText) {
            updateTask(task.id, newTaskText);
            li.textContent = newTaskText;
            li.appendChild(editButton);
            li.appendChild(deleteButton);
        }
    };

    // Delete button
    const deleteButton = document.createElement('button');
    deleteButton.textContent = 'Delete';
    deleteButton.className = 'delete';
    deleteButton.onclick = function(event) {
        event.stopPropagation(); // Prevent triggering the click event on the li
        deleteTask(task.id);
        taskList.removeChild
