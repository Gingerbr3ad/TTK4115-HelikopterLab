% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring

PORT = 3;

%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
elevation_offset = 0.5;
Joystick_gain_x = 2;
Joystick_gain_y = -0.5;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

%%%%%%%%%%% Controller constants
V_s0 = 8.05;
K_f = (g*(2*m_p*l_h - m_c*l_c))/(l_h*V_s0);
K1 = (K_f)/(2*m_p*l_p);
K2 = (l_h*K_f)/(m_c*l_c^2 + 2*m_p*l_h^2);
K3 = (g*(2*m_p*l_h - m_c*l_c))/(m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2));

%%%%%%%%%%% Controller parameters
q1 = 300;
q2 = 400;
q3 = 1000;
q4 = 35;
q5 = 1000;

r1 = 1;
r2 = 1;

A = [0 1 0 0 0
     0 0 0 0 0
     0 0 0 0 0
    -1 0 0 0 0
     0 0 -1 0 0];
 
B = [0 0
    0 K1
    K2 0
    0 0
    0 0];

G = [0 0
     0 0
     0 0
     1 0
     0 1];

Q =[q1 0 0 0 0
    0 q2 0 0 0
    0 0 q3 0 0
    0 0 0 q4 0
    0 0 0 0 q5];

R = [r1 0
    0 r2];

K = lqr(A, B, Q, R);

F = [K(1,1) K(1,3)
     K(2,1) K(2,3)];

 
%%%%%%%%%%% Luenberger Observere

A_obs = [0 1 0 0 0
         0 0 0 0 0
         0 0 0 1 0
         0 0 0 0 0
         K3 0 0 0 0];

B_obs = [0 0
         0 K1
         0 0
         K2 0
         0 0];

C = [1 0 0 0 0
     0 1 0 0 0
     0 0 1 0 0
     0 0 0 1 0
     0 0 0 0 1];

p = [-12, -7, -8, -35, -9];

Obsv = obsv(A_obs,C);
R_Obsv = rank(Obsv)

L = place(A_obs', C', p)';
 
load("Pre_R_stationary.mat");
R_stationary = cov(Pre_R_stationary);
load("Pre_R_flying.mat");
R_flying = cov(Pre_R_flying);
