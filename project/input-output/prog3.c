#include <stdio.h>
int main() {
int _jjj;
int _iii;
int _xxx;
int _bbb;
int _aaa;

printf("Enter _aaa: ");
scanf("%d", &_aaa);
printf("Enter _bbb: ");
scanf("%d", &_bbb);
for(
_xxx = _aaa;
_xxx <= _bbb;
++_xxx
) printf("%d\n", (_xxx * _xxx));
_xxx = 0;
for(
_iii = 1;
_iii <= _aaa;
++_iii
) for(
_jjj = 1;
_jjj <= _bbb;
++_jjj
) _xxx = (_xxx + 1);
printf("%d\n", _xxx);
return 0;
}
