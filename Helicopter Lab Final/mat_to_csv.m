matPath = '/home/wiktor/Code/TTK4115-HelikopterLab/Helicopter Lab Final/Lab_1/Tests_new/Test_exponentail_decay_negative_pitch_bias.mat';
fields = {'time', 'pitch', 'elevation', 'travel'};

S = load(matPath);
data = S.ans.';

T = array2table(data, 'VariableNames', fields);
[folder, name] = fileparts(matPath);
writetable(T, fullfile(folder, [name '.csv']));
