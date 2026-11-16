matPath = '/home/wiktor/Code/TTK4115-HelikopterLab/Helicopter Lab Final/Lab_4/Tests/Test6.mat';
fields = {'time', 'Vf_sat', 'Vb_sat', 'V_s', 'V_d', 'p_c', 'e_dot_c', 'p~', 'e~', 'p_hat', 'e_hat', 'p_dot_hat', 'e_dot_hat', 'lambda_hat', 'lambda_dot_hat', 'p_dot~', 'e_dot~', 'lambda_dot~', 'p', 'e', 'p_dot', 'e_dot'};

S = load(matPath);
data = S.ans.';

T = array2table(data, 'VariableNames', fields);
[folder, name] = fileparts(matPath);
writetable(T, fullfile('/home/wiktor/Code/TTK4115-HelikopterLab/Tests_converted/Lab_4', [name '.csv']));
