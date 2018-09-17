(in-package #:core)

(eval-when (:load-toplevel) ; don't bother with this when loading source.
  (macrolet ((stupify (package)
               (let (collect)
                 (do-external-symbols (s package)
                   (when (and (fboundp s)
                              (typep (fdefinition s) 'generic-function))
                     (push s collect))
                   (let ((setf `(setf ,s)))
                     (when (and (fboundp setf)
                                (typep (fdefinition setf) 'generic-function))
                       (push setf collect))))
                 `(progn
                    ,@(loop for s in collect
                            collecting `(clos::satiate-from-experience ,s)))))
             (stupify-all ()
               `(progn
                  ,@(loop for p in (list-all-packages)
                          collect `(stupify ,p)))))
    #+(stupify-all)
    (stupify "CLEAVIR-GENERATE-AST")
    (stupify "CLEAVIR-AST-TO-HIR")
    (stupify "CLEAVIR-COMPILATION-POLICY")
    (stupify "CLEAVIR-IR")
    (stupify "CLEAVIR-AST")
    (stupify "CLEAVIR-ENVIRONMENT")
    (stupify "CLEAVIR-IO")
    (stupify "CLEAVIR-METER")
    (stupify "CLASP-CLEAVIR")
    (stupify "CLASP-CLEAVIR-AST")
    (stupify "CLASP-CLEAVIR-AST-TO-HIR")
    (stupify "CLASP-CLEAVIR-HIR")
    (stupify "CC-MIR")
    (stupify "CC-GENERATE-AST")
    (stupify "CC-HIR-TO-MIR")))
