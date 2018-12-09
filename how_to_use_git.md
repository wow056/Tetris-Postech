Git 및 GitLab 사용 방법: 강민수 작성
=======================
## 1. Git 설치
 <https://git-scm.com/downloads> 링크에서 git 을 다운받아 설치해주세요.
## 2. SSH Key 업로드
1. 시작 메뉴에서 **git bash**를 찾아 실행해주세요
2. 다음과 같이 입력해주세요  
    `ssh-keygen -t rsa -C "GitLab" -b 4096`

    passpharse를 입력하라는 부분은 공란으로 두고, y/n으로 물어볼 땐 y를 입력하면 됩니다.  
    `Generating public/private rsa key pair.`  
    `Enter file in which to save the key (/Users/사용자명/.ssh/id_rsa): `  
    `Enter passphrase (empty for no passphrase): `  
    `Enter same passphrase again: `  

 3. 다음과 같이 입력하면 생성된 ssh key가 클립보드에 복사됩니다.  
    `cat ~/.ssh/id_rsa.pub | clip`  
 4. <https://gitlab.com/> 사이트에 들어가 **설정>SSH키**에 들어갑니다.
 5. 복사한 ssh key 를 key 란에 붙여넣고 **키 추가**를 누릅니다.
 6. **git bash**에서 다음과 같이 입력해주세요.  
    `ssh -T git@gitlab.com`  
    다음과 같이 출력되면 성공입니다.  
    `Welcome to GitLab, @wow056!`  


그림과 함께 보시려면 <http://dejavuqa.tistory.com/139>에서 확인해주세요.
## Git 사용법
### 1. 프로젝트 가져오기
1. **git bash**를 실행시켜, 원하는 폴더로 이동한 뒤 다음과 같이 입력해주세요.  
    ssh 모드  
    `git clone git@gitlab.com:ugrp_fv/ugrp_fv.git`  
    https 모드(위의 명령어가 안 될때)  
    `https://gitlab.com/ugrp_fv/ugrp_fv.git`
2. ugrp_fv 라는 폴더에 프로젝트가 복사된 것을 확인할 수 있습니다.

### 2. 커밋
커밋은 개발한 프로젝트를 중간 저장하는 것을 말합니다. 커밋을 하면 로그에 지금까지 변경한 수정 사항이 기록되어, gitlab에 업로드할 중간 지점을 설정하거나 잘못 개발한 프로젝트를 되돌릴 수 있습니다.  
1. 원하는 수준까지 코드를 작성하였을 경우 다음 명령어로 수정 사항을 확인할 수 있습니다.  
    `git diff`  
2. 코드를 커밋할 때는 다음과 같이 입력하세요  
    `git add 파일명`  
    파일명은 **변경사항이 커밋에 반영되길 원하는 파일명**입니다.  
    모든 파일을 커밋하기 원할 때는 `git add .`를 입력해주세요.
3. 커밋할 코드가 제대로 추가되었는지 확인하기 위해서는 `git diff`를 입력해주세요.
3. `git commit -m '커밋 메시지'`  
    커밋 메시지에는 코드에 어떤 수정을 했는지 적어주세요. 커밋 메시지를 작성해야 커밋이 됩니다.



### 3. 풀
다른 사람이 업로드한 수정사항은 풀 명령어로 가져올 수 있습니다. 다음 명령어를 입력하세요.  
        `git pull`

### 4. 푸쉬
커밋한 변경 내용을 서버에 업로드하는 명령어입니다. 다음 명령어를 입력하세요  
        `git push`

### 5. 코드 되돌리기
1. 마지막 커밋으로 변경 사항을 **되돌리고** 싶을 때에는
    `git checkout -- 파일명`  
    전체를 되돌리고 싶을 때에는
    `git checkout -- .`  
    마지막 커밋 후 작성된 내용이 모두 사라지기 때문에 내용을 보존하고 싶을 때는 우선 커밋을 해주세요.
2. 커밋 후 커밋 전으로 돌아가기  
    `git checkout HEAD~1`  이 명령어는 1번 커밋하기 전으로 돌아가도록 해줍니다.  
    `git checkout HEAD~10`  이 명령어는 10번 커밋하기 전으로 돌아가줍니다.  
    원래 상태로 돌아오기 위해서는  
    `git checkout master`  를 입력해주면 됩니다.  
