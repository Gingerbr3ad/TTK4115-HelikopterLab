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


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
elevation_offset = 0.5;
Joystick_gain_x = 1.5;
Joystick_gain_y = -6;


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
K_1 = (K_f)/(2*m_p*l_p);

%%%%%%%%%%% Controller parameters
%%% Oscilatory Growth
%  pole1 = 0.002 + 2i;
%  pole2 = 0.002 - 2i;
%%% Exponential Growth
% pole1 = 0.002;
% pole2 = 0.002;
%%% Stable Oscilations
% pole1 = 0.5i;
% pole2 = -0.5i;
%%% Oscilatory Decay
% pole1 = -2 + 3i;
% pole2 = -2 - 3i;
%%% Exponential Decay
pole1 = -2;
pole2 = -2;

Kpp = (pole1*pole2)/K_1;
Kpd = -(pole1+pole2)/K_1;
