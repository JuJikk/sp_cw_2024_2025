#include <stdio.h>
int main() {
int _ccc;
int _bbb;
int _aaa;

printf("Enter _aaa: ");
scanf("%d", &_aaa);
printf("Enter _bbb: ");
scanf("%d", &_bbb);
printf("Enter _ccc: ");
scanf("%d", &_ccc);
if ((_aaa < _bbb)) if ((_aaa < _ccc)) printf("%d\n", _aaa);
 else printf("%d\n", _ccc);

 else if ((_bbb < _ccc)) printf("%d\n", _bbb);
 else printf("%d\n", _ccc);


if (((_aaa == _bbb) && ((_aaa == _ccc) && (_bbb == _ccc)))) printf("%d\n", 1);
 else printf("%d\n", 0);

if (((_aaa > 0) || ((_bbb > 0) || (_ccc > 0)))) printf("%d\n", -1);
 else printf("%d\n", 0);

if (!((_aaa > (_bbb + _ccc)))) printf("%d\n", 10);
 else printf("%d\n", 0);

return 0;
}
