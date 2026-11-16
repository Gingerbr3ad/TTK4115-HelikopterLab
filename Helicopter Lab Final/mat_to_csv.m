matPath = '/home/wiktor/Code/TTK4115-HelikopterLab/Helicopter Lab Final/Lab_2/Tests_integral/Test.mat';
fields = {'time', 'p_c', 'e_c', 'lambda~', 'lambda_dot~', 'p~', 'p~dot', 'e~', 'e_dot~', 'Vf_sat', 'Vb_sat'};

S = load(matPath);
data = S.ans.';

T = array2table(data, 'VariableNames', fields);
[folder, name] = fileparts(matPath);
writetable(T, fullfile('/home/wiktor/Code/TTK4115-HelikopterLab/Tests_converted/Lab_2/integral', [name '.csv']));
