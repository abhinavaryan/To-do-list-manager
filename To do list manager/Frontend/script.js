document.getElementById('add-task').addEventListener('click', function() {
    const taskInput = document.getElementById('task-input');
    const taskText = taskInput.value;

    if (taskText) {
        fetch('http://localhost:3000/tasks', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    title: taskText
                })
            })
            .then(response => response.text())
            .then(data => {
                console.log(data);
                taskInput.value = '';
                loadTasks();
            });
    }
});

function loadTasks() {
    fetch('http://localhost:3000/tasks')
        .then(response => response.json())
        .then(tasks => {
            const taskList = document.getElementById('task-list');
            taskList.innerHTML = '';
            tasks.forEach((task, index) => {
                const li = document.createElement('li');
                li.textContent = task.title;
                li.addEventListener('click', () => {
                    fetch(`http://localhost:3000/tasks/${task.id}`, {
                            method: 'DELETE'
                        })
                        .then(() => loadTasks());
                });
                taskList.appendChild(li);
            });
        });
}

loadTasks();