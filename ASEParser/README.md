# ASE Parser



--------------

22. 07. 06
기존에 만들어서 사용했던 ASE Parser를 DLL화 시킴
원래는 프로젝트 내부에서 객체 생성까지 했었지만 생성은 Factory에서 하는 것으로 바꾸고
ASE Parser DLL은 데이터를 Parsing해서 들고 있는 것까지만 한다.