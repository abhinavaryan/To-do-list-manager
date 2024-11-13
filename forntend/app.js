async function addTask() {
    const taskInput = document.getElementById('taskInput');
    const task = taskInput.value;
    if (task) {
        const response = await fetch('/api/todos', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ task })
        });
        taskInput.value = '';
        loadTasks();
    }
}

async function loadTasks() {
    const response = await fetch('/api/todos');
    const tasks = await response.json();
    const taskList = document.getElementById('taskList');
    taskList.innerHTML = '';
    tasks.forEach(task => {
        const li = document.createElement('li');
        li.textContent = task;
        taskList.appendChild(li);
    });
}

window.onload = loadTasks;