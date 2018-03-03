
-- test error handling, i forgot to restore Warn_restart in
-- the trigger handler once. the errors and subsequent core dump were
-- interesting.

SELECT invalid_type_uncaught('rick');
SELECT invalid_type_caught('rick');
SELECT invalid_type_reraised('rick');
SELECT valid_type('rick');

-- Security sandbox tests
SELECT read_file('/etc/passwd');
SELECT write_file('/tmp/plpython','This is very bad');
SELECT getpid();
SELECT uname();
SELECT sys_exit();
SELECT sys_argv();
