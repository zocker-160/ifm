;;; Example highlight definitions for IFM mode.

(hilit-set-mode-patterns 'ifm-mode
 '(
   ;; Comments.
   ("#.*" nil firebrick)
   ;; Strings.
   (hilit-string-find ?\\ grey40)
   ;; Include files.
   ("^[ \t]*include\\b.*" nil purple)
   ;; Styles.
   ("^\\(style\\|endstyle\\)" nil forestgreen)
   ;; Sections.
   ("^[ \t]*\\(map\\|title\\)[ \t]" nil red)
   ;; Rooms.
   ("^[ \t]*\\broom[ \t]" nil blue-bold)
   ;; Other commands.
   ("^[ \t]*\\b\\(item\\|link\\|join\\|task\\)[ \t]" nil royalblue)
   ;; Directions.
   ;; ("\\b\\(d\\|down\\|e\\|east\\|n\\|ne\\|north\\|northeast\\|northwest\\|nw\\|s\\|se\\|south\\|southeast\\|southwest\\|sw\\|u\\|up\\|w\\|west\\)\\b" nil black)
   ;; Keywords.
   ;; ("\\b\\(after\\|all\\|any\\|before\\|cmd\\|dir\\|drop\\|except\\|exit\\|finish\\|follow\\|from\\|get\\|give\\|given\\|go\\|goto\\|hidden\\|in\\|it\\|item\\|join\\|keep\\|last\\|leave\\|length\\|link\\|lose\\|lost\\|need\\|nolink\\|nopath\\|none\\|note\\|oneway\\|out\\|safe\\|score\\|start\\|style\\|tag\\|task\\|times\\|to\\|undef\\|until\\)\\b" nil royalblue)
   ))
