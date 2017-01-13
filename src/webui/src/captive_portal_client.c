
/*  Dowse - embedded WebUI based on Kore.io
 *
 *  (c) Copyright 2016 Dyne.org foundation, Amsterdam
 *  Written by Nicola Rossi <nicola@dyne.org>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include <webui.h>

int captive_portal_client(struct http_request * req) {
    template_t tmpl;
    char *html_rendered;
    struct kore_buf *out;
    attributes_set_t attr;
    int len;
    out = kore_buf_alloc(0);
    int bad_parsing=0;
    attr = attrinit();
	/**/
    WEBUI_DEBUG;
    http_populate_get(req);

    PARSE_PARAMETER(macaddr);

    CHECK_PARAMETER();

    char sql[256];
    snprintf(sql,sizeof(sql),"INSERT INTO event (level,macaddr,description) VALUES ('warning','%s','%s') ",macaddr,__EVENT_NEW_MAC_ADDRESS);

    int rv = sqlexecute(sql, &attr);
    if (rv != KORE_RESULT_OK) {
        return show_generic_message_page(req,attr);
    }
    /**/

    template_load(asset_captive_portal_client_html,asset_len_captive_portal_client_html,&tmpl);
    template_apply(&tmpl,global_attributes,out);

	/**/
    WEBUI_DEBUG;
    html_rendered = kore_buf_release(out, &len);
    http_response(req, 200, html_rendered, len);

    /**/
    WEBUI_DEBUG;
    kore_free(html_rendered);

    return (KORE_RESULT_OK);
}
