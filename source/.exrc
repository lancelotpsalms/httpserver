if &cp | set nocp | endif
noremap  h
let s:cpo_save=&cpo
set cpo&vim
noremap <NL> j
noremap  k
noremap  l
map \mbt <Plug>TMiniBufExplorer
map \mbu <Plug>UMiniBufExplorer
map \mbc <Plug>CMiniBufExplorer
map \mbe <Plug>MiniBufExplorer
nmap \ihn :IHN
nmap \is :IHS:A
nmap \ih :IHS
map at :call AddTitle():$o
nmap gx <Plug>NetrwBrowseX
nmap wm :WMToggle
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
imap \ihn :IHN
imap \is :IHS:A
imap \ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set cindent
set completeopt=longest,menu
set cscopequickfix=s-,c-,d-,i-,t-,e-
set noequalalways
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=cn
set history=50
set nomodeline
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim73,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set shiftwidth=4
set softtabstop=4
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=4
set tags=../tags,../include/tags,./include/tags,.,./tags,./usr/include/tags
" vim: set ft=vim :
