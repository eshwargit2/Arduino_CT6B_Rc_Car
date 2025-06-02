<h1>Arduino RC Car</h1>

in Arduino CT6B transmitter and Receiver using make the RC car .in without speed only for a move a diraction using for a channel 1 and channel 2 in without speed using a speed control for a channel 3 is a speed diraction for a car

<ul>
<li>Arduino</li> 
<li>L298N Motor Driver</li>
<li>CT6B Transmiter and Receiver</li>
<li>4 DC Motor</li>
<li>lithium iron Battery</li>
<li>Jumper Wire</li>
</ul>


-------------<h1>Wire Connections</h1>


<h3> Arduino to CT6B Receiver </h3>
<p>Without speed</p>
<ul>
  <li>Arduino[ A0 ] ---------- throttlePin - CH2 </li>
  <li>Arduino[ A1 ] ---------- steeringPin - CH1 </li>
</ul>

<h3> Arduino to CT6B   Receiver </h3>
<p>With speed</p>
<ul>
  <li>Arduino[ A0 ] ---------- throttlePin - CH2 </li>
  <li>Arduino[ A1 ] ---------- steeringPin - CH1 </li>
  <li>Arduino[ A2 ] ---------- SpeedPin - CH3 </li>
</ul>

<h3> Arduino to L298N Motor Driver </h3>
<ul>
  <li>Arduino[ D3 ] ---------- ENA </li>
  <li>Arduino[ D5 ] ---------- IN1 </li>
  <li>Arduino[ D6 ] ---------- IN2 </li>
  <li>Arduino[ D11 ] ---------- ENB </li>
  <li>Arduino[ D9 ] ---------- IN3 </li>
  <li>Arduino[ D10   ] ---------- IN4 </li>
</ul>

