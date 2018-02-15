iconv -f CP-1251 -t UTF-8//IGNORE file
#discards any unsupported characters.

iconv -f CP-1251 -t UTF-8//TRANSLIT file
#attempts to substitute similar characters from the target encoding