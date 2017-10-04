((nil . ((eval . (set (make-local-variable 'my-project-path)
                      (file-name-directory
                       (let ((d (dir-locals-find-file ".")))
                         (if (stringp d) d (car d))))))
         ;; (cmake-ide-project-dir . my-project-path)
         (eval . (setq cmake-ide-build-dir (concat my-project-path "build")))
         (cmake-ide-cmake-opts . "-DCMAKE_CXX_COMPILER=clang++ -DCATCH_INCLUDE_DIR=~/src/Catch/include -GNinja"))))
