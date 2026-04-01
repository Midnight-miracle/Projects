/* ──────────────────────────────────────────
   logic.js  –  To-Do List
   ────────────────────────────────────────── */

const STORAGE_KEY = 'todo_tasks';

// ── DOM refs ──────────────────────────────
const taskInput   = document.getElementById('taskInput');
const addBtn      = document.getElementById('addBtn');
const taskList    = document.getElementById('taskList');
const taskCount   = document.getElementById('taskCount');
const emptyMsg    = document.getElementById('emptyMsg');
const clearDoneBtn = document.getElementById('clearDoneBtn');
const clearAllBtn  = document.getElementById('clearAllBtn');

// ── State ─────────────────────────────────
let tasks = loadTasks();

// ── Init ──────────────────────────────────
renderAll();

// ── Event listeners ───────────────────────
addBtn.addEventListener('click', handleAdd);

taskInput.addEventListener('keydown', (e) => {
  if (e.key === 'Enter') handleAdd();
});

clearDoneBtn.addEventListener('click', () => {
  tasks = tasks.filter(t => !t.done);
  saveTasks();
  renderAll();
});

clearAllBtn.addEventListener('click', () => {
  if (tasks.length === 0) return;
  if (confirm('Clear ALL tasks? This cannot be undone.')) {
    tasks = [];
    saveTasks();
    renderAll();
  }
});

// ── Handlers ──────────────────────────────
function handleAdd() {
  const text = taskInput.value.trim();
  if (!text) {
    taskInput.focus();
    taskInput.classList.add('shake');
    taskInput.addEventListener('animationend', () => taskInput.classList.remove('shake'), { once: true });
    return;
  }

  tasks.push({ id: Date.now(), text, done: false });
  saveTasks();
  renderAll();

  taskInput.value = '';
  taskInput.focus();
}

function toggleTask(id) {
  const task = tasks.find(t => t.id === id);
  if (task) task.done = !task.done;
  saveTasks();
  renderAll();
}

function deleteTask(id) {
  tasks = tasks.filter(t => t.id !== id);
  saveTasks();
  renderAll();
}

// ── Render ────────────────────────────────
function renderAll() {
  taskList.innerHTML = '';

  tasks.forEach(task => {
    const li = document.createElement('li');
    li.className = 'task-item' + (task.done ? ' done' : '');

    const checkbox = document.createElement('input');
    checkbox.type = 'checkbox';
    checkbox.checked = task.done;
    checkbox.addEventListener('change', () => toggleTask(task.id));

    const label = document.createElement('span');
    label.className = 'task-label';
    label.textContent = task.text;
    label.addEventListener('click', () => toggleTask(task.id));

    const delBtn = document.createElement('button');
    delBtn.className = 'delete-btn';
    delBtn.innerHTML = '✕';
    delBtn.title = 'Delete task';
    delBtn.addEventListener('click', () => deleteTask(task.id));

    li.append(checkbox, label, delBtn);
    taskList.appendChild(li);
  });

  // Count badge
  const total = tasks.length;
  const done  = tasks.filter(t => t.done).length;
  taskCount.textContent = total ? `${done}/${total}` : '';

  // Empty state
  emptyMsg.style.display = total === 0 ? 'block' : 'none';
}

// ── Persistence ───────────────────────────
function saveTasks() {
  try {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(tasks));
  } catch (e) {
    console.warn('Could not save tasks to localStorage:', e);
  }
}

function loadTasks() {
  try {
    const stored = localStorage.getItem(STORAGE_KEY);
    return stored ? JSON.parse(stored) : [];
  } catch (e) {
    console.warn('Could not load tasks from localStorage:', e);
    return [];
  }
}

/* ── Optional: shake animation for empty input ──
   Add this to style.css if you haven't already:

@keyframes shake {
  0%, 100% { transform: translateX(0); }
  25%       { transform: translateX(-6px); }
  75%       { transform: translateX(6px); }
}
.shake { animation: shake 0.25s ease; }
*/
