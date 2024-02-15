clc;
clear;
close all;

%% 产生仿真信号
fs = 1000;                  % 采样频率
t = (0:1/fs:1-1/fs);        % 时间
f = 10;                     % 信号频率
x = sin(2*pi*f*t+pi/3);     % 原始信号
y = awgn(x,15,'measured');  % 添加高斯白噪声后的信号
%% LMS自适应滤波
L = 20;     % 滤波器阶数
Mu = 0.005;   % μ的范围为0到1
xn = y;     % 输入信号
dn = x;     % 期望信号
[yn, W, en] = LMS(xn,dn,L,Mu);
%% 画图
figure;
subplot(3,1,1);plot(t,x);xlabel('时间/s');ylabel('幅值');title('原始信号');
subplot(3,1,2);plot(t,y);xlabel('时间/s');ylabel('幅值');title('LMS滤波器输入信号');
subplot(3,1,3);plot(t,yn);xlabel('时间/s');ylabel('幅值');title('LMS滤波器输出信号');
figure;plot(en);title('误差信号收敛情况');
%% fonction
function [yn, W, en] = LMS(xn, dn, M, mu)
% 输入参数:
%   xn   输入的信号，为一行序列
%   dn   所期望的响应
%   M    滤波器的阶数
%   mu   收敛因子(步长)
% 输出参数:
%   W    滤波器系数矩阵  
%   en   误差序列 
%   yn   滤波器输出

[m,n] = size(xn);
if m>1  % 如果输入信号为一列，则进行转置
    xn = xn';
end
if m>1 && n>1
    fprintf('输入信号有误！请检查输入信号是否为一行序列');
end

itr = n;    % 迭代次数等于输入信号的长度
en = zeros(1,itr);      % 初始化误差信号
W  = zeros(M,itr);    % 初始化权值矩阵，每一列代表一次迭代

% 迭代计算
for k = M:itr                   % 第k次迭代
    x = xn(k:-1:k-M+1);         % 滤波器M个抽头的输入
    y = x*W(:,k-1);             % 滤波器的输出
    en(k) = dn(k)-y;            % 第k次迭代的误差
    W(:,k) = W(:,k-1)+2*mu*en(k)*x';     % 滤波器权值计算的迭代式
end

yn = inf * ones(size(xn));      % 初值为无穷大作为绘图使用，无穷大处不会绘图
for k = M:n
    x = xn(k:-1:k-M+1);
    yn(k) = x*W(:,end);  % 最终输出结果
end
end
