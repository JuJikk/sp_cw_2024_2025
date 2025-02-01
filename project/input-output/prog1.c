#include <stdio.h>
int main() {
int _yyy;
int _xxx;
int _bbb;
int _aaa;

printf("Enter _aaa: ");
scanf("%d", &_aaa);
printf("Enter _bbb: ");
scanf("%d", &_bbb);
printf("%d\n", (_aaa + _bbb));
printf("%d\n", (_aaa - _bbb));
printf("%d\n", (_aaa * _bbb));
printf("%d\n", (_aaa / _bbb));
printf("%d\n", (_aaa % _bbb));
_xxx = (((_aaa - _bbb) * 10) + ((_aaa + _bbb) / 10));
_yyy = (_xxx + (_xxx % 10));
printf("%d\n", _xxx);
printf("%d\n", _yyy);
return 0;
}
