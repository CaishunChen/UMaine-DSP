function [ info, varargout ] = ece486( id, varargin )
%ECE486 Save/Get a collection of matlab variables to/from a database
%
% ece486(student_id_number);
%   Initialization call for the beginning of each matlab session.  This call
%   registers the student with the database server.  If "student_id_number"
%   is not provided on the first call, the user is prompted for the value.
%
% ece486(id, var1, var2, ....)
%   saves the varables var1, var2, ... to a database using the identifier
%   provided by the variable "id".  "id" is normally a short string. 
%
% vars = ece486(id);
%   Retrieves the previously submitted collection of variables for the 
%   tag given by "id".  The values are returned in a cell array, so that
%   vars{1} contains the value of "var1", vars{2} contains "var2", and so on.
%
% [info, var1, var2, ...] = ece486(id)
%   Retrieves a database entry information structure "info" along with the 
%   previously submitted collection of variables for the tag given by "id".
%
% The saved variables var1, var2, etc., may be numeric arrays or strings.
%
% Within a given Matlab session, repeated calls to the database using the 
% same "id" replaces all previously saved data for that id tag.

persistent REGISTRATIONSTRING;  % String needed for submissions
persistent USERID;              % Student ID

% %%%%%%%  DATABASE ACCESS FUNCTIONS %%%%%%%%%%%%%%%%
dbase_url = 'http://192.168.1.1/';
%mlock;

if (isempty(REGISTRATIONSTRING))
    %
    % First call...  We need to send the user's student ID to the database
    % server to register the user.  The server will give us a string to use
    % for all subsequent calls.
    %
    if (~exist('id','var'))
        % Registration call with no arguments.  
        % Ask for student ID, register, and return.
        USERID = input('Enter Student ID number: ');
        [REGISTRATIONSTRING] = init_database_server(USERID, dbase_url);
        return;
    elseif (nargin==1 & isnumeric(id) )
        % Registration call with student-id given as only argument.
        % Record student ID, register, and return.
        USERID = id;
        [REGISTRATIONSTRING] = init_database_server(USERID, dbase_url);
        return;
    else
        % Trying to access database before registering
        % Prompt for student id, register, and continue processing request
        USERID = input('Enter Student ID number: ');
        REGISTRATIONSTRING = init_database_server(USERID, dbase_url);
    end;
end;

% First argument should be an id tag. (String or single number)
assert( ischar(id) | (isnumeric(id) & length(id)==1), ...
    'ece486(): First argument should be id string');
id = num2str(id);   % Make the id into a character string.


if (nargin == 1)
    % For only one argument, query the database and return a cell array of 
    % previously submitted arguments

    % ****** Get the string from the database using the id tag *****
    [info, dbase_string] = database_access(USERID, REGISTRATIONSTRING, id, dbase_url);
    
    varargout = eval(dbase_string); % Parse the string to get the matlab variables

    if (nargout==1)
        info = varargout;  % For only one output... just return the cell array
    end;
    return;
else
    % For more than one input argument, we are submitting data to the database
    dbase_string = ['{ '];  % Open cell array
    dbase_string =[dbase_string mat2str(varargin{1}) ]; % First matrix
    for i=2:length(varargin)
        dbase_string = [dbase_string ', ' mat2str(varargin{i}) ]; 
    end
    dbase_string = [dbase_string ' };']; % End cell array string
    
    % ****** Now submit the string to the database *****
    info = database_submit(USERID, REGISTRATIONSTRING, id, dbase_string, dbase_url);

end
return;
end



%% Database registration
function reg_string = init_database_server(id, dbase_url)


% Generate URL based on dabase_base
access_string = strcat(dbase_url, 'register.php');

% Execute command
reg_string = urlread(access_string, 'post', {'student_id', int2str(id)})

return;
end



%% Database submission to record a character string
function status = database_submit(student_id, registration, id, dbase_string, dbase_url)

access_string = strcat(dbase_url, 'submit.php');

status = urlread(access_string, 'post', {'secret_id', registration, 'question_id', id, 'filter', dbase_string});

end



%% Database Access to retrieve a character string.
function [status, result] = database_access(student_id, registration, id, dbase_url)

access_string = strcat(dbase_url, 'check.php');

result = urlread(access_string, 'post', {'secret_id', registration, 'question_id', id});

status.id_tag = id;     % Phony database request status structure...
status.student_id = student_id;
status.submit_time = '12:34am Jan 15, 2015';

return;
end
