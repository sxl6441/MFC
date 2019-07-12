void dlg_test1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	ProError status = PRO_TK_NO_ERROR;
	//ProSelection feature_sel;
	//ProSelection *sels = NULL;
	//int sel_n;
	//status = ProSelect("feature", 1, NULL, NULL, NULL, NULL, &sels, &sel_n);
	//if (status != PRO_TK_NO_ERROR || sel_n < 1) {
	//	return;
	//}
	//status = ProSelectionCopy(sels[0], &feature_sel);
	//if (status != PRO_TK_NO_ERROR) { return; }
	//ProFeature pipeline;
	//status = ProSelectionPipelineGet(feature_sel, &pipeline);
	//return;
	//ProModelitem item;
	//ProFeature feat;
	//ProFeatStatus feat_status;
	//status = ProSelectionModelitemGet(feature_sel, &item);
	//if (status != PRO_TK_NO_ERROR) { return; }
	//status = ProFeatureInit((ProSolid)feature_sel->part_ptr, item.id, &feat);
	//if (status != PRO_TK_NO_ERROR) { return; }
	//status = ProFeatureStatusGet(&feat, &feat_status);
	//if (status != PRO_TK_NO_ERROR) { return; }
	//ProWindowRepaint(-1);
	ProMdl curr_mdl;
	status = ProMdlCurrentGet(&curr_mdl);
	ProLnstk *lnsks = NULL;
	int lnsks_n;
	status = ProAssemblyLnstksCollect((ProAssembly)curr_mdl, &lnsks);
	ProArraySizeGet(lnsks, &lnsks_n);
	for (int i = 0; i < lnsks_n; i++) {
	}
	ProFeature feat;
	status = ProModelitemByNameInit(curr_mdl, PRO_FEATURE, L"TESTP", &feat);
	if (status != PRO_TK_NO_ERROR) {
		return;
	}
	ProFeattype feat_type;
	status = ProFeatureTypeGet(&feat, &feat_type);
	ProPnetwork works;
	int works_n;
	status = ProPipelineNetworkEval(&feat, &works);
	if (status != PRO_TK_NO_ERROR) {
		return;
	}
	vector<ProPextension>PextS;
	status = ProPnetworkExtensionVisit(works, UserProPextensionVisitAction, NULL, &PextS);
	for (int j = 0; j < PextS.size(); j++) {
		vector<ProPmember>pmembers;
		status = ProPextensionMemberVisit(PextS[j], UserProPmemberVisitAction, NULL, &pmembers);
		for (int k = 0; k < pmembers.size(); k++) {
			vector<ProPobject>PobjectS;
			ProPmemberType type;
			status = ProPmemberTypeGet(pmembers[k], &type);
			if (type == PROPMEMBERTYPE_TERMINATOR) {
				ProPterminator terminator;
				status = ProPmemberTerminatorGet(pmembers[k], &terminator);
				ProPobject Pobject;
				if (status == PRO_TK_NO_ERROR) {
					status = ProPterminatorObjectGet(terminator, &Pobject);
					PobjectS.push_back(Pobject);
				}
			}
			else if (type == PROPMEMBERTYPE_JUNCTION) {
				ProPjunction junction;
				status = ProPmemberJunctionGet(pmembers[k], &junction);
				if (status == PRO_TK_NO_ERROR) {
					ProPobject Pobject;
					status = ProPjunctionObjectGet(junction, &Pobject);
					PobjectS.push_back(Pobject);
				}
			}
			else if (type == PROPMEMBERTYPE_SERIES) {
				ProPseries Pseries;
				status = ProPmemberSeriesGet(pmembers[k], &Pseries);
				if (status == PRO_TK_NO_ERROR) {
					status = ProPseriesObjectVisit(Pseries, UserProPseriesObjectVisit, NULL, &PobjectS);
				}
			}
			for (int l = 0; l < PobjectS.size(); l++) {
				ProPobjectType object_type;
				status = ProPobjectTypeGet(PobjectS[l], &object_type);
				if (object_type != PROPOBJECTTYPE_SEGMENT) { continue; }
				ProPstubin stubin;
				status = ProPobjectStubinGet(PobjectS[l], &stubin);
				if (status == PRO_TK_NO_ERROR) {
					ProPoint point = NULL;
					status = ProPstubinPointGet(stubin, &point);
					if (status == PRO_TK_NO_ERROR) {
						ProVector xyz;
						status = ProPointCoordGet(point, xyz);
					}
				}
				ProPsegment segment;
				status = ProPobjectSegmentGet(PobjectS[l], &segment);
				if (status != PRO_TK_NO_ERROR) {
					continue;
				}
				ProPsegmentType type;
				status = ProPsegmentTypeGet(segment, &type);
				double length;
				status = ProPsegmentLengthGet(segment, &length);
				ProCurve *curves = NULL;
				status = ProPsegmentCurvesGet(segment, &curves);
				int curves_n;
				status = ProArraySizeGet(curves, &curves_n);
				for (int m = 0; m < curves_n; m++) {
					ProGeomitemdata *cure_data = NULL;
					status = ProCurveDataGet(curves[m], &cure_data);
					if (status != PRO_TK_NO_ERROR) {
						continue;
					}

				}
			}
		}
	}
}
