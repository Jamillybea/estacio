<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>Jenga Nexus — Jogue Agora!</title>
<style>
  *{margin:0;padding:0;box-sizing:border-box;}
  body{background:#050510;color:#fff;font-family:'Segoe UI',sans-serif;overflow:hidden;}
  #game-container{position:fixed;top:0;left:0;width:100%;height:100%;}
  .ui{position:fixed;top:20px;left:20px;right:20px;display:flex;justify-content:space-between;z-index:10;flex-wrap:wrap;gap:10px;}
  .card{background:rgba(0,0,0,0.8);border-radius:20px;padding:12px 20px;backdrop-filter:blur(10px);border:1px solid #ffd966;}
  .stats{display:flex;gap:20px;}
  .stat-value{font-size:28px;font-weight:bold;color:#4caf50;}
  .stat-label{font-size:10px;color:#aaa;}
  .buttons{position:fixed;bottom:20px;left:20px;right:20px;display:flex;justify-content:center;gap:15px;z-index:10;}
  button{padding:12px 24px;font-size:14px;font-weight:bold;border:none;border-radius:12px;cursor:pointer;text-transform:uppercase;}
  .reset{background:#ff9800;color:white;}
  .vr{background:#00bcd4;color:white;}
  .sound{background:#9c27b0;color:white;}
  .toast{position:fixed;bottom:100px;left:50%;transform:translateX(-50%) translateY(100px);background:#667eea;color:white;padding:10px 20px;border-radius:12px;z-index:100;transition:transform 0.3s;white-space:nowrap;}
  .toast.show{transform:translateX(-50%) translateY(0);}
  @media(max-width:768px){.stat-value{font-size:18px;}button{padding:8px 16px;font-size:12px;}.card{padding:8px 12px;}}
</style>
</head>
<body>
<div id="game-container"></div>
<div class="ui">
  <div class="card"><div class="stats"><div><div class="stat-value" id="score">0</div><div class="stat-label">PONTOS</div></div><div><div class="stat-value" id="moves">0</div><div class="stat-label">JOGADAS</div></div><div><div class="stat-value" id="blocks">36</div><div class="stat-label">BLOCOS</div></div></div></div>
</div>
<div class="buttons">
  <button class="reset" id="resetBtn">🔄 RECOMEÇAR</button>
  <button class="vr" id="vrBtn">🕶️ VISÃO VR</button>
  <button class="sound" id="soundBtn">🔊 SOM</button>
</div>
<div class="toast" id="toast">Clique nos blocos para remover!</div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/three@0.128.0/examples/js/controls/OrbitControls.js"></script>
<script>
// Configuração
const container = document.getElementById('game-container');
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x0a0e27);
scene.fog = new THREE.FogExp2(0x0a0e27, 0.008);

const camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.set(8, 6, 10);

const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.shadowMap.enabled = true;
container.appendChild(renderer.domElement);

const controls = new THREE.OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.enableZoom = true;
controls.target.set(0, 3, 0);

// Luzes
const ambient = new THREE.AmbientLight(0x404060);
scene.add(ambient);
const mainLight = new THREE.DirectionalLight(0xffffff, 1);
mainLight.position.set(5, 10, 7);
mainLight.castShadow = true;
scene.add(mainLight);
const grid = new THREE.GridHelper(15, 20, 0x88aaff, 0x335588);
grid.position.y = -0.4;
scene.add(grid);

// Variáveis
const BLOCK_W = 0.9, BLOCK_H = 0.3, BLOCK_D = 0.9;
const colors = [0xd4af37, 0xc41e3a, 0x4c8c4a, 0x5d3a1a, 0x2c5f8a, 0x9b59b6, 0xe67e22];
let blocks = [];
let blockId = 1;
let score = 0, moves = 0, gameActive = true;
let soundOn = true;
let audioCtx = null;
let vrMode = false;

function playSound(freq=800, dur=0.15){
  if(!soundOn) return;
  if(!audioCtx) audioCtx = new (AudioContext||webkitAudioContext)();
  if(audioCtx.state==='suspended') audioCtx.resume();
  const osc = audioCtx.createOscillator();
  const gain = audioCtx.createGain();
  osc.connect(gain);
  gain.connect(audioCtx.destination);
  osc.frequency.value = freq;
  gain.gain.value = 0.2;
  gain.gain.exponentialRampToValueAtTime(0.00001, audioCtx.currentTime + dur);
  osc.start();
  osc.stop(audioCtx.currentTime + dur);
}

function vibrate(dur=30){ if(navigator.vibrate) navigator.vibrate(dur); }

function buildTower(levels=12){
  blocks.forEach(b=>{ if(b.mesh) scene.remove(b.mesh); });
  blocks = [];
  blockId = 1;
  for(let lvl=0; lvl<levels; lvl++){
    const isHoriz = lvl%2===0;
    let offX=0, offZ=0;
    if(isHoriz){ offX=-BLOCK_W; offZ=0; }
    else{ offX=0; offZ=-BLOCK_D; }
    for(let i=0;i<3;i++){
      let x,z;
      if(isHoriz){ x=offX+i*BLOCK_W; z=0; }
      else{ x=0; z=offZ+i*BLOCK_D; }
      const y = lvl*BLOCK_H;
      const rot = isHoriz?0:Math.PI/2;
      const geo = new THREE.BoxGeometry(BLOCK_W, BLOCK_H, BLOCK_D);
      const mat = new THREE.MeshStandardMaterial({ color: colors[Math.floor(Math.random()*colors.length)], roughness:0.3 });
      const mesh = new THREE.Mesh(geo, mat);
      mesh.position.set(x, y, z);
      mesh.rotation.y = rot;
      mesh.castShadow = true;
      mesh.userData = { id: blockId, level: lvl };
      scene.add(mesh);
      blocks.push({ mesh, id: blockId, x, y, z, level: lvl });
      blockId++;
    }
  }
  updateUI();
}

function applyGravity(){
  const byLevel = {};
  blocks.forEach(b=>{ if(!byLevel[b.level]) byLevel[b.level]=[]; byLevel[b.level].push(b); });
  let fallen=false;
  for(let lvl=0;lvl<20;lvl++){
    if((byLevel[lvl]||[]).length===0 && lvl>0){
      (byLevel[lvl+1]||[]).forEach(block=>{
        const targetY = lvl*BLOCK_H;
        if(block.mesh.position.y > targetY+0.05){
          fallen=true;
          block.mesh.position.y -= 0.08;
        }
      });
    }
  }
  return fallen;
}

function fallBlock(block){
  const interval = setInterval(()=>{
    if(block.mesh.position.y > -2){
      block.mesh.position.y -= 0.1;
      block.mesh.rotation.x += 0.08;
      block.mesh.rotation.z += 0.05;
    } else {
      clearInterval(interval);
      scene.remove(block.mesh);
    }
  },16);
}

function particles(pos){
  for(let i=0;i<12;i++){
    const geo = new THREE.SphereGeometry(0.05,4,4);
    const mat = new THREE.MeshStandardMaterial({ color:0xffaa66 });
    const p = new THREE.Mesh(geo, mat);
    p.position.copy(pos);
    scene.add(p);
    const vx = (Math.random()-0.5)*0.2;
    const vy = Math.random()*0.2;
    const vz = (Math.random()-0.5)*0.2;
    let life=0;
    const int = setInterval(()=>{
      life++;
      p.position.x += vx;
      p.position.y += vy;
      p.position.z += vz;
      p.scale.multiplyScalar(0.92);
      if(life>25){ clearInterval(int); scene.remove(p); }
    },33);
  }
}

function collapse(){
  gameActive=false;
  playSound(200,0.6);
  vibrate([200,100,200]);
  showToast("💥 TORRE DESMORONOU! Fim de jogo!");
  blocks.forEach(block=>{
    const int = setInterval(()=>{
      if(block.mesh.position.y>-2){
        block.mesh.position.y -= 0.08;
        block.mesh.rotation.x += 0.05;
      } else { clearInterval(int); scene.remove(block.mesh); }
    },16);
  });
}

function removeBlock(block){
  if(!gameActive) return;
  const above = blocks.filter(b=>b.level>block.level);
  const isTop = above.length===0;
  if(!isTop && Math.random()<0.25){ collapse(); return; }
  const points = isTop?50:100;
  score+=points;
  moves++;
  fallBlock(block);
  particles(block.mesh.position);
  playSound(800,0.15);
  vibrate(30);
  const idx = blocks.findIndex(b=>b.id===block.id);
  if(idx!==-1) blocks.splice(idx,1);
  showToast(`+${points} pontos!`);
  setTimeout(()=>{
    if(applyGravity()) showToast("⚠️ Torre tremeu!");
    if(blocks.length<=3){
      gameActive=false;
      playSound(1200,0.5);
      showToast("🏆 VOCÊ VENCEU! 🏆");
    }
    updateUI();
  },100);
  updateUI();
}

function updateUI(){
  document.getElementById('score').textContent=score;
  document.getElementById('moves').textContent=moves;
  document.getElementById('blocks').textContent=blocks.length;
}

function showToast(msg){
  const t=document.getElementById('toast');
  t.textContent=msg;
  t.classList.add('show');
  setTimeout(()=>t.classList.remove('show'),2000);
}

function reset(){
  gameActive=true;
  score=0;
  moves=0;
  buildTower(12);
  showToast("🔄 Jogo reiniciado!");
}

function toggleVR(){
  vrMode=!vrMode;
  if(vrMode){
    camera.position.set(0,2.5,3.5);
    controls.target.set(0,2.5,0);
    showToast("🕶️ Modo VR");
  } else {
    camera.position.set(8,6,10);
    controls.target.set(0,3,0);
    showToast("👁️ Modo Normal");
  }
  controls.update();
}

function toggleSound(){
  soundOn=!soundOn;
  document.getElementById('soundBtn').innerHTML = soundOn?'🔊 SOM':'🔇 SOM';
  if(soundOn) playSound(800,0.1);
}

// Cliques
const raycaster = new THREE.Raycaster();
const mouse = new THREE.Vector2();

function onClick(e){
  if(!gameActive) return;
  const rect = renderer.domElement.getBoundingClientRect();
  const x = ((e.clientX-rect.left)/rect.width)*2-1;
  const y = -((e.clientY-rect.top)/rect.height)*2+1;
  mouse.set(x,y);
  raycaster.setFromCamera(mouse,camera);
  const hits = raycaster.intersectObjects(blocks.map(b=>b.mesh));
  if(hits.length){
    const block = blocks.find(b=>b.mesh===hits[0].object);
    if(block){
      hits[0].object.material.emissiveIntensity=0.6;
      setTimeout(()=>{if(hits[0].object.material) hits[0].object.material.emissiveIntensity=0.1;},150);
      removeBlock(block);
    }
  }
}

window.addEventListener('click',onClick);
document.getElementById('resetBtn').onclick=reset;
document.getElementById('vrBtn').onclick=toggleVR;
document.getElementById('soundBtn').onclick=toggleSound;

function animate(){
  requestAnimationFrame(animate);
  controls.update();
  renderer.render(scene,camera);
}

buildTower(12);
animate();

window.addEventListener('resize',()=>{
  camera.aspect=window.innerWidth/window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth,window.innerHeight);
});

// Ativar áudio
function enableAudio(){ if(audioCtx?.state==='suspended') audioCtx.resume(); document.removeEventListener('click',enableAudio); }
document.addEventListener('click',enableAudio);
</script>
</body>
</html>
